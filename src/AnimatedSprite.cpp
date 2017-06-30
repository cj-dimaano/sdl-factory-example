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
    : Sprite(spritesheet, framesRegion, drawRegion), _frameDelay(frameDelay),
      _frameTick(0), _frameCount(frameCount), _currentFrame(0), _isPaused(true),
      _framesRegion(framesRegion) {
  SetSpriteRegionSize(frameHeight, frameWidth);
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
  int x = _framesRegion.x +
          (_currentFrame % (_framesRegion.w / spriteRegion.w)) * spriteRegion.w;
  int y = _framesRegion.y +
          (_currentFrame / (_framesRegion.w / spriteRegion.w)) * spriteRegion.h;
  printf("%d, %d\n", x, y);
  spriteRegion.x = x;
  spriteRegion.y = y;
}

void AnimatedSprite::SetFrameCount(const int value) { _frameCount = value; }

void AnimatedSprite::SetFramesRegion(SDL_Rect value) {
  _framesRegion = value;
  SetFrame(0);
}

void AnimatedSprite::SetFramesRegionPoint(const int x, const int y) {
  _framesRegion.x = x;
  _framesRegion.y = y;
  SetFrame(0);
}

void AnimatedSprite::SetFramesRegionSize(const int height, const int width) {
  _framesRegion.h = height;
  _framesRegion.w = width;
  SetFrame(0);
}

void AnimatedSprite::Update(unsigned int dt) {
  _frameTick += (_isPaused ? 0 : dt);
  if (_frameTick > _frameDelay) {
    _frameTick = _frameTick % _frameDelay;
    SetFrame(_currentFrame + 1);
  }
}
