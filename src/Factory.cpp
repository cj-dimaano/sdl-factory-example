/*******************************************************************************
@file `Factory.cpp`
  Created July 6, 2017

@author CJ Dimaano
  <c.j.s.dimaano@gmail.com>
*******************************************************************************/

#include "Factory.h"

static SDL_Rect makeRect(int x, int y, int w, int h) {
  SDL_Rect r;
  r.x = x;
  r.y = y;
  r.w = w;
  r.y = y;
  return r;
}

static SDL_Point makePoint(int x, int y) {
  SDL_Point p;
  p.x = x;
  p.y = y;
  return p;
}

static void RefreshCandidates(std::vector<StructureMachine *> &candidates,
                              std::vector<RobotMachine> &robots,
                              StructureMachine *remove, bool isEmpty) {
  std::vector<StructureMachine *> newCandidates;
  for (StructureMachine *m : candidates) {
    if (m != remove)
      newCandidates.push_back(m);
  }
  candidates.swap(newCandidates);
  for (RobotMachine &r : robots) {
    if (r.IsPickingTarget() && r.IsEmpty() == isEmpty)
      r.PickTarget(candidates);
  }
}

Factory::Factory(SDL_Texture *factorySpritesheet, int x, int y, int width,
                 int height)
    : spritesheet(factorySpritesheet),
      tile(
          Sprite(spritesheet, makeRect(16, 0, 16, 16), makeRect(0, 0, 32, 32))),
      drawPoint(makePoint(x, y)), factorySize(makePoint(width, height)) {}

void Factory::Update(unsigned int dt) {
  for (ConsumerMachine &c : consumers)
    c.Update(dt);
  for (ProducerMachine &p : producers)
    p.Update(dt);
  for (RobotMachine &r : robots) {
    double progress = r.GetStepProgress() + 1;
    SDL_Point p = r.GetFactoryPoint();
    r.SetDrawPoint(drawPoint.x + static_cast<int>(p.x * 16 * progress),
                   drawPoint.x + static_cast<int>(p.y * 8 * progress));
    r.Update(dt);
  }
}

void Factory::Draw(SDL_Renderer *sdlRenderer) {
  for (int i = 0; i < factorySize.x; i++) {
    for (int j = 0; j < factorySize.y / 2; j++) {
      tile.SetDrawRegionPoint(drawPoint.x + i * 16, drawPoint.y + j * 16);
      tile.Draw(sdlRenderer);
    }
  }
}

void Factory::AddConsumerMachine(int x, int y) {
  ConsumerMachine c(spritesheet,
                    makeRect(drawPoint.x + x * 16, drawPoint.y + y * 8, 16, 16),
                    makePoint(x, y));
  EventPayload<Machine> payload(&c);
  c.AddIsIdleChangedEventHandler(
      std::bind(&Factory::ConsumerIsIdleChanged, this, payload));
  consumers.push_back(c);
  candidateConsumers.push_back(&consumers.back());
}

void Factory::AddProducerMachine(int x, int y) {
  ProducerMachine p(spritesheet,
                    makeRect(drawPoint.x + x * 16, drawPoint.y + y * 8, 16, 16),
                    makePoint(x, y));
  EventPayload<Machine> payload(&p);
  p.AddIsIdleChangedEventHandler(
      std::bind(&Factory::ProducerIsIdleChanged, this, payload));
  producers.push_back(p);
  candidateProducers.push_back(&producers.back());
}

void Factory::AddRobotMachine(int x, int y) {
  RobotMachine r(spritesheet,
                 makeRect(drawPoint.x + x * 16, drawPoint.y + y * 8, 16, 16),
                 makePoint(x, y));
  EventPayload<RobotMachine> payload(&r);
  r.AddHasTargetChangedEventHandler(
      std::bind(&Factory::HasTargetChanged, this, payload));
  robots.push_back(r);
}

void Factory::HasTargetChanged(EventPayload<RobotMachine> &payload) {
  bool isEmpty = payload.source->IsEmpty();
  if (payload.source->HasTarget())
    RefreshCandidates(isEmpty ? candidateProducers : candidateConsumers, robots,
                      payload.source->GetTarget(), isEmpty);
  else
    payload.source->PickTarget(isEmpty ? candidateProducers
                                       : candidateConsumers);
}

void Factory::ConsumerIsIdleChanged(EventPayload<Machine> &payload) {
  if (payload.source->IsIdle())
    candidateConsumers.push_back(
        dynamic_cast<StructureMachine *>(payload.source));
}

void Factory::ProducerIsIdleChanged(EventPayload<Machine> &payload) {
  if (payload.source->IsIdle())
    candidateProducers.push_back(
        dynamic_cast<StructureMachine *>(payload.source));
}
