/*******************************************************************************
@file `RobotMachine.cpp`
  Created July 5, 2017

@author CJ Dimaano
  <c.j.s.dimaano@gmail.com>
*******************************************************************************/

#include "RobotMachine.h"

#define HAS_TARGET_CHANGED_EVENT "RobotMachine::HasTargetChanged"

static SDL_Point makePoint(int x, int y) {
  SDL_Point p = {x, y};
  return p;
}

static SDL_Rect makeRect(int x, int y, int w, int h) {
  SDL_Rect r = {x, y, w, h};
  return r;
}

static std::vector<SDL_Point> getNeighbors(SDL_Point p) {
  std::vector<SDL_Point> neighbors;
  neighbors.push_back(makePoint(p.x, p.y - 1));
  neighbors.push_back(makePoint(p.x - 1, p.y - 1));
  neighbors.push_back(makePoint(p.x - 1, p.y));
  neighbors.push_back(makePoint(p.x - 1, p.y + 1));
  neighbors.push_back(makePoint(p.x, p.y + 1));
  neighbors.push_back(makePoint(p.x + 1, p.y + 1));
  neighbors.push_back(makePoint(p.x + 1, p.y));
  neighbors.push_back(makePoint(p.x + 1, p.y + 1));
  return neighbors;
}

RobotMachine::RobotMachine(SDL_Texture *spritesheet, SDL_Rect drawRegion,
                           SDL_Point factoryPoint)
    : Machine(AnimatedSprite(spritesheet, makeRect(0, 48, 32, 16), drawRegion,
                             16, 16, 2, 100),
              factoryPoint, 500),
      _pickTarget(
          std::bind(&RobotMachine::SetTargetPath, this,
                    std::pair<StructureMachine *, std::vector<SDL_Point>>()),
          &getNeighbors),
      _stepDelay(500), _stepTick(0), _isEmpty(true),
      _emptySpriteRegion(makeRect(0, 48, 32, 16)),
      _fullSpriteRegion(makeRect(0, 64, 32, 16)), _target(NULL) {
  EventEmitter<RobotMachine>::AddEvent(HAS_TARGET_CHANGED_EVENT);
  EventPayload<Machine> payload(this);
  AddIsIdleChangedEventHandler(
      std::bind(&RobotMachine::IsIdleChanged, this, payload));
}

void RobotMachine::AddHasTargetChangedEventHandler(
    std::function<void(EventPayload<RobotMachine> &)> handler) {
  EventEmitter<RobotMachine>::AddEventHandler(HAS_TARGET_CHANGED_EVENT,
                                              handler);
}

void RobotMachine::PickTarget(std::vector<StructureMachine *> candidates) {
  _pickTarget.Begin(GetFactoryPoint(), candidates);
}

void RobotMachine::OnHasTargetChanged() {
  EventPayload<RobotMachine> payload(this);
  EventEmitter<RobotMachine>::EmitEvent(HAS_TARGET_CHANGED_EVENT, payload);
}

void RobotMachine::OnUpdate(unsigned int dt) {
  _stepTick = _path.empty() ? 0 : _stepTick + dt;
  if (_stepTick >= _stepDelay) {
    _stepTick -= _stepDelay;
    SetFactoryPoint(_path.back());
    _path.pop_back();
    if (_path.empty() && _target != NULL && _target->IsIdle()) {
      SDL_Point targetPoint = _target->GetFactoryPoint();
      SDL_Point thisPoint = GetFactoryPoint();
      if (targetPoint.x == thisPoint.x && targetPoint.y == thisPoint.y)
        Restart();
      else {
        _target = NULL;
        OnHasTargetChanged();
      }
    }
  }
  _pickTarget.Next();
}

void RobotMachine::SetTargetPath(
    std::pair<StructureMachine *, std::vector<SDL_Point>> &targetPath) {
  _target = targetPath.first;
  _path = targetPath.second;
  OnHasTargetChanged();
}

void RobotMachine::IsIdleChanged(EventPayload<Machine> &) {
  if (IsIdle()) {
    _target = NULL;
    _isEmpty = !_isEmpty;
    GetMachineSprite().SetSpriteRegion(_isEmpty ? _emptySpriteRegion
                                                : _fullSpriteRegion);
    OnHasTargetChanged();
  }
}