/*******************************************************************************
@file `ConsumerMachine.cpp`
  Created June 29, 2017

@author CJ Dimaano
  <c.j.s.dimaano@gmail.com>
*******************************************************************************/

#include "ConsumerMachine.h"

static SDL_Rect makeSDL_Rect(int x, int y, int w, int h) {
  SDL_Rect r = {x, y, w, h};
  return r;
}

ConsumerMachine::ConsumerMachine(SDL_Texture *const spritesheet,
                                 SDL_Rect drawRegion, SDL_Point factoryPoint)
    : StructureMachine(spritesheet, makeSDL_Rect(0, 16, 32, 16),
                       makeSDL_Rect(16, 16, 32, 16),
                       makeSDL_Rect(48, 0, 32, 80), drawRegion, factoryPoint,
                       3000) {}
