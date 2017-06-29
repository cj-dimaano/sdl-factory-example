/*******************************************************************************
@file `Sprite.cpp`
  Created June 28, 2017

@author CJ Dimaano
  <c.j.s.dimaano@gmail.com>
*******************************************************************************/

#include "Sprite.h"

static void SetRegionPoint(SDL_Rect &dst, const int x, const int y) {
  dst.x = x;
  dst.y = y;
}

static void SetRegionSize(SDL_Rect &dst, const int height, const int width) {
  dst.h = height;
  dst.w = width;
}

Sprite::Sprite(SDL_Texture *const spritesheet, const SDL_Rect spriteRegion,
               const SDL_Rect drawRegion)
    : _spritesheet(spritesheet), _spriteRegion(spriteRegion),
      _drawRegion(drawRegion) {}

SDL_Rect &Sprite::GetSpriteRegion() { return _spriteRegion; }

void Sprite::SetSpriteRegion(const SDL_Rect value) { _spriteRegion = value; }

void Sprite::SetSpriteRegionPoint(const int x, const int y) {
  SetRegionPoint(_spriteRegion, x, y);
}

void Sprite::SetSpriteRegionSize(const int height, const int width) {
  SetRegionSize(_spriteRegion, height, width);
}

SDL_Rect &Sprite::GetDrawRegion() { return _drawRegion; }

void Sprite::SetDrawRegion(const SDL_Rect value) { _drawRegion = value; }

void Sprite::SetDrawRegionPoint(const int x, const int y) {
  SetRegionPoint(_drawRegion, x, y);
}

void Sprite::SetDrawRegionSize(const int height, const int width) {
  SetRegionSize(_drawRegion, height, width);
}

void Sprite::Draw(SDL_Renderer *const sdlRenderer) {
  SDL_RenderCopy(sdlRenderer, _spritesheet, &_spriteRegion, &_drawRegion);
}
