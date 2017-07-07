/*******************************************************************************
@file `RobotMachine.cpp`
  Created July 5, 2017

@author CJ Dimaano
  <c.j.s.dimaano@gmail.com>
*******************************************************************************/

#include "RobotMachine.h"

#define HAS_TARGET_CHANGED_EVENT "RobotMachine::HasTargetChanged"

static SDL_Point makePoint(int x, int y) {
  SDL_Point p;
  p.x = x;
  p.y = y;
  return p;
}

static SDL_Rect makeRect(int x, int y, int w, int h) {
  SDL_Rect r;
  r.x = x;
  r.y = y;
  r.w = w;
  r.h = h;
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
              factoryPoint, 1000),
      _pickTarget(new PickTargetAlgorithm(
          [this](std::pair<StructureMachine *, std::vector<SDL_Point>>
                     &targetPath) { this->SetTargetPath(targetPath); },
          &getNeighbors)),
      _stepDelay(100), _stepTick(0), _isEmpty(true), _isPickingTarget(false),
      _emptySpriteRegion(makeRect(0, 48, 32, 16)),
      _fullSpriteRegion(makeRect(0, 64, 32, 16)), _target(NULL) {
  EventEmitter<RobotMachine>::AddEvent(HAS_TARGET_CHANGED_EVENT);
  EventPayload<Machine> payload(this);
  AddIsIdleChangedEventHandler(
      [this](EventPayload<Machine> &payload) { this->IsIdleChanged(payload); });
}

RobotMachine::~RobotMachine() { delete _pickTarget; }

void RobotMachine::AddHasTargetChangedEventHandler(
    std::function<void(EventPayload<RobotMachine> &)> handler) {
  EventEmitter<RobotMachine>::AddEventHandler(HAS_TARGET_CHANGED_EVENT,
                                              handler);
}

void RobotMachine::PickTarget(std::vector<StructureMachine *> candidates) {
  _isPickingTarget = true;
  _pickTarget->Begin(GetFactoryPoint(), candidates);
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
  _pickTarget->Next();
}

void RobotMachine::SetTargetPath(
    std::pair<StructureMachine *, std::vector<SDL_Point>> &targetPath) {
  _isPickingTarget = false;
  _target = targetPath.first;
  _path = targetPath.second;
  OnHasTargetChanged();
}

void RobotMachine::IsIdleChanged(EventPayload<Machine> &) {
  if (IsIdle()) {
    SDL_Point targetPoint = _target->GetFactoryPoint();
    SDL_Point thisPoint = GetFactoryPoint();
    if (targetPoint.x == thisPoint.x && targetPoint.y == thisPoint.y)
      _target->Restart();
    _target = NULL;
    _isEmpty = !_isEmpty;
    GetMachineSprite().SetFramesRegion(_isEmpty ? _emptySpriteRegion
                                                : _fullSpriteRegion);
    OnHasTargetChanged();
  }
}