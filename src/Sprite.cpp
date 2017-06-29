/*******************************************************************************
@file `Sprite.cpp`
  Created June 28, 2017

@author CJ Dimaano
  <c.j.s.dimaano@gmail.com>
*******************************************************************************/

#include "Sprite.h"

Sprite::Sprite(SDL_Texture *const spritesheet, const SDL_Rect spriteRegion,
               const SDL_Rect drawRegion) {
  _spritesheet = spritesheet;
  _spriteRegion = spriteRegion;
  _drawRegion = drawRegion;
}

SDL_Rect &Sprite::GetSpriteRegion() { return _spriteRegion; }

void Sprite::SetSpriteRegion(const SDL_Rect value) { _spriteRegion = value; }

SDL_Rect &Sprite::GetDrawRegion() { return _drawRegion; }

void Sprite::SetDrawRegion(const SDL_Rect value) { _drawRegion = value; }

void Sprite::Draw(SDL_Renderer *const sdlRenderer) {
  SDL_RenderCopy(sdlRenderer, _spritesheet, &_spriteRegion, &_drawRegion);
}
