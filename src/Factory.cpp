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
  r.h = h;
  return r;
}

static SDL_Point makePoint(int x, int y) {
  SDL_Point p;
  p.x = x;
  p.y = y;
  return p;
}

static void RefreshCandidates(std::vector<StructureMachine *> &candidates,
                              std::vector<RobotMachine *> &robots,
                              StructureMachine *remove, bool isEmpty) {
  std::vector<StructureMachine *> newCandidates;
  for (StructureMachine *m : candidates) {
    if (m != remove)
      newCandidates.push_back(m);
  }
  candidates.swap(newCandidates);
  for (RobotMachine *r : robots) {
    if (r->IsPickingTarget() && r->IsEmpty() == isEmpty)
      r->PickTarget(candidates);
  }
}

Factory::Factory(SDL_Texture *factorySpritesheet, int x, int y, int width,
                 int height)
    : spritesheet(factorySpritesheet),
      tile(
          Sprite(spritesheet, makeRect(16, 0, 16, 16), makeRect(0, 0, 32, 32))),
      drawPoint(makePoint(x, y)), factorySize(makePoint(width, height)) {}

Factory::~Factory() {
  for (ConsumerMachine *c : consumers)
    delete c;
  for (ProducerMachine *p : producers)
    delete p;
  for (RobotMachine *r : robots)
    delete r;
}

void Factory::Update(unsigned int dt) {
  for (ConsumerMachine *c : consumers)
    c->Update(dt);
  for (ProducerMachine *p : producers)
    p->Update(dt);
  for (RobotMachine *r : robots) {
    r->Update(dt);
    double progress = r->GetStepProgress();
    SDL_Point p = r->GetFactoryPoint();
    SDL_Point q = r->GetStep();
    q.x -= p.x;
    q.y -= p.y;
    r->SetDrawPoint(drawPoint.x + (p.x + (double)q.x * progress) * 32,
                    drawPoint.y + (p.y + (double)q.y * progress) * 16);
  }
}

void Factory::Draw(SDL_Renderer *sdlRenderer) {
  for (int i = 0; i < factorySize.x; i++) {
    for (int j = 0; j < (factorySize.y + 1) / 2; j++) {
      tile.SetDrawRegionPoint(drawPoint.x + i * 32, drawPoint.y + j * 32);
      tile.Draw(sdlRenderer);
    }
  }
  for (ConsumerMachine *c : consumers)
    c->Draw(sdlRenderer);
  for (ProducerMachine *p : producers)
    p->Draw(sdlRenderer);
  for (RobotMachine *r : robots)
    r->Draw(sdlRenderer);
}

void Factory::AddConsumerMachine(int x, int y) {
  ConsumerMachine *c = new ConsumerMachine(
      spritesheet, makeRect(drawPoint.x + x * 32, drawPoint.y + y * 16, 32, 32),
      makePoint(x, y));
  c->AddIsIdleChangedEventHandler([this](EventPayload<Machine> &payload) {
    this->ConsumerIsIdleChanged(payload);
  });
  consumers.push_back(c);
  candidateConsumers.push_back(c);
}

void Factory::AddProducerMachine(int x, int y) {
  ProducerMachine *p = new ProducerMachine(
      spritesheet, makeRect(drawPoint.x + x * 32, drawPoint.y + y * 16, 32, 32),
      makePoint(x, y));
  p->AddIsIdleChangedEventHandler([this](EventPayload<Machine> &payload) {
    this->ProducerIsIdleChanged(payload);
  });
  producers.push_back(p);
  candidateProducers.push_back(p);
}

void Factory::AddRobotMachine(int x, int y) {
  RobotMachine *r = new RobotMachine(
      spritesheet, makeRect(drawPoint.x + x * 32, drawPoint.y + y * 16, 32, 32),
      makePoint(x, y));
  EventPayload<RobotMachine> payload(r);
  r->AddHasTargetChangedEventHandler(
      [this](EventPayload<RobotMachine> &payload) {
        this->HasTargetChanged(payload);
      });
  r->PickTarget(candidateProducers);
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
