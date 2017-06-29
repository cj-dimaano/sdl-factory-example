/*******************************************************************************
@file `Machine.cpp`
  Created June 29, 2017

@author CJ Dimaano
  <c.j.s.dimaano@gmail.com>
*******************************************************************************/

#include "Machine.h"

Machine::Machine(AnimatedSprite sprite, SDL_Point factoryPoint,
                 unsigned int busyDelay)
    : _busyDelay(busyDelay), _busyTick(busyDelay), _factoryPoint(factoryPoint),
      _sprite(sprite), _isPaused(true) {
  _sprite.Play();
}

Machine::~Machine() {}

void Machine::Update(unsigned int dt) {
  _busyTick += (_isPaused || IsReady() ? 0 : dt);
  _sprite.Update(dt);
  if (!_isPaused && IsReady()) {
    Pause();
    OnIdle();
  }
  OnUpdate(dt);
}

bool Machine::IsReady() { return _busyTick >= _busyDelay; }

void Machine::Start() { _isPaused = false; }

void Machine::Pause() { _isPaused = true; }

void Machine::Restart() {
  Reset();
  Start();
  OnBusy();
}

void Machine::Reset() { _busyTick = 0; }

unsigned int Machine::GetProgress() {
  return (_busyTick > _busyDelay ? 100 : 100 * _busyTick / _busyDelay);
}

SDL_Point &Machine::GetFactoryPoint() { return _factoryPoint; }

void Machine::SetFactoryPoint(SDL_Point value) { _factoryPoint = value; }

void Machine::SetFactoryPoint(const int x, const int y) {
  _factoryPoint.x = x;
  _factoryPoint.y = y;
}

void Machine::SetDrawPoint(const int x, const int y) {
  _sprite.SetDrawRegionPoint(x, y);
}

AnimatedSprite &Machine::GetMachineSprite() { return _sprite; }

void Machine::OnUpdate(unsigned int) {}

void Machine::OnBusy() {}

void Machine::OnIdle() {}
