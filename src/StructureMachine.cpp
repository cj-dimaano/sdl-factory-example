/*******************************************************************************
@file `StructureMachine.cpp`
  Created June 29, 2017

@author CJ Dimaano
  <c.j.s.dimaano@gmail.com>
*******************************************************************************/

#include "StructureMachine.h"
#include <functional>

static void SetRegionPoint(SDL_Rect &dst, const int x, const int y) {
  dst.x = x;
  dst.y = y;
}

StructureMachine::StructureMachine(SDL_Texture *const spritesheet,
                                   SDL_Rect busySpriteRegion,
                                   SDL_Rect idleSpriteRegion,
                                   SDL_Rect progressSpriteRegion,
                                   SDL_Rect drawRegion, SDL_Point factoryPoint,
                                   unsigned int busyDelay)
    : Machine(AnimatedSprite(spritesheet, idleSpriteRegion, drawRegion, 16, 16,
                             2, 1000),
              factoryPoint, busyDelay),
      _progressSprite(spritesheet, progressSpriteRegion, drawRegion, 16, 16, 10,
                      100),
      _busySpriteRegion(busySpriteRegion), _idleSpriteRegion(idleSpriteRegion) {
  AddIsIdleChangedEventHandler(
      [this](EventPayload<Machine> &) { this->IsIdleChanged(); });
  IsIdleChanged();
}

void StructureMachine::Draw(SDL_Renderer *sdlRenderer) {
  GetMachineSprite().Draw(sdlRenderer);
  _progressSprite.Draw(sdlRenderer);
}

void StructureMachine::SetDrawPoint(const int x, const int y) {
  GetMachineSprite().SetDrawRegionPoint(x, y);
  _progressSprite.SetDrawRegionPoint(x, y);
  SetRegionPoint(_busySpriteRegion, x, y);
  SetRegionPoint(_idleSpriteRegion, x, y);
}

void StructureMachine::OnUpdate(unsigned int dt) {
  if (IsIdle())
    _progressSprite.Update(dt);
  else
    _progressSprite.SetFrame(9 * GetProgress() / 100);
}

void StructureMachine::IsIdleChanged() {
  if (IsIdle()) {
    _progressSprite.SetFramesRegionPoint(48, 64);
    _progressSprite.SetFrameCount(2);
    _progressSprite.Play();
    GetMachineSprite().SetFramesRegion(_idleSpriteRegion);
  } else {
    _progressSprite.SetFramesRegionPoint(48, 0);
    _progressSprite.SetFrameCount(10);
    _progressSprite.Pause();
    GetMachineSprite().SetFramesRegion(_busySpriteRegion);
  }
}
