/*******************************************************************************
@file `ConsumerMachine.h`
  Created June 29, 2017

@author CJ Dimaano
  <c.j.s.dimaano@gmail.com>
*******************************************************************************/

#ifndef CONSUMERMACHINE_H
#define CONSUMERMACHINE_H

#include "StructureMachine.h"
#include <SDL2/SDL.h>

/**
 * `ConsumerMachine`
 *
 *   Represents a factory machine that consumes a payload.
 */
class ConsumerMachine : public StructureMachine {

public:
  /**
   * `ConsumerMachine`
   *
   *   Constructor.
   *
   * @param spritesheet
   *   The SDL texture containing the sprites.
   *
   * @param drawRegion
   *   The region of the renderer where the machine will be drawn.
   *
   * @param factoryPoint
   *   The factory coordinates of the machine.
   */
  ConsumerMachine(SDL_Texture *const spritesheet, SDL_Rect drawRegion,
                  SDL_Point factoryPoint);
};

#endif
