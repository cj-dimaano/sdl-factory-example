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
  consumers.push_back(c);
}

void Factory::AddProducerMachine(int x, int y) {
  ProducerMachine p(spritesheet,
                    makeRect(drawPoint.x + x * 16, drawPoint.y + y * 8, 16, 16),
                    makePoint(x, y));
  producers.push_back(p);
}

void Factory::AddRobotMachine(int x, int y) {
  RobotMachine r(spritesheet,
                 makeRect(drawPoint.x + x * 16, drawPoint.y + y * 8, 16, 16),
                 makePoint(x, y));
  robots.push_back(r);
}
