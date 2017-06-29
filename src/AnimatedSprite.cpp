/*******************************************************************************
@file `AnimatedSprite.cpp`
  Created Jun 28, 2017

@author CJ Dimaano
  <c.j.s.dimaano@gmail.com>
*******************************************************************************/

#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(SDL_Texture *const spritesheet,
                               const SDL_Rect framesRegion,
                               const SDL_Rect drawRegion, const int frameHeight,
                               const int frameWidth, const int frameCount,
                               const unsigned int frameDelay)
    : Sprite(spritesheet, framesRegion, drawRegion) {
  SetSpriteRegionSize(frameHeight, frameWidth);

  _framesRegion = framesRegion;
  _frameCount = frameCount;
  _frameDelay = frameDelay;
  _frameTick = 0;
  _currentFrame = 0;
  _isPaused = true;
}

void AnimatedSprite::Play() { _isPaused = false; }

void AnimatedSprite::Pause() { _isPaused = true; }

void AnimatedSprite::Restart() { SetFrame(0); }

void AnimatedSprite::SetFrameDelay(const unsigned int value) {
  _frameDelay = value;
}

void AnimatedSprite::SetFrame(const int index) {
  SDL_Rect &spriteRegion = GetSpriteRegion();
  _currentFrame = index % _frameCount;
  spriteRegion.x =
      _framesRegion.x + _currentFrame * spriteRegion.w % _framesRegion.w;
  spriteRegion.y =
      _framesRegion.y + _currentFrame * spriteRegion.h % _framesRegion.h;
}

void AnimatedSprite::Update(unsigned int dt) {
  _frameTick += (_isPaused ? 0 : dt);
  if (_frameTick > _frameDelay) {
    _frameTick = _frameTick % _frameDelay;
    SetFrame(_currentFrame + 1);
  }
}
