/*******************************************************************************
@file `StructureMachine.h`
  Created June 29, 2017

@author CJ Dimaano
  <c.j.s.dimaano@gmail.com>
*******************************************************************************/

#ifndef STRUCTUREMACHINE_H
#define STRUCTUREMACHINE_H

#include "AnimatedSprite.h"
#include "Machine.h"
#include <SDL2/SDL.h>

/**
 * `StructureMachine`
 *
 *   Represents a stationary factory machine.
 */
class StructureMachine : public Machine {

  /**
   * `_busySpriteRegion`
   *
   *   The spritesheet region of the animation representing a busy machine.
   */
  SDL_Rect _busySpriteRegion;

  /**
   * `_idleSpriteRegion`
   *
   *   The spritesheet region of the animation representing an idle machine.
   */
  SDL_Rect _idleSpriteRegion;

  /**
   * `_progressSprite`
   *
   *   The animated sprite of the progress bar.
   */
  AnimatedSprite _progressSprite;

public:
  /**
   * `StructureMachine`
   *
   *   Constructor.
   *
   * @param spritesheet
   *   The SDL texture containing the sprites.
   *
   * @param busySpriteRegion
   *   The spritesheet region of the animation representing a busy machine.
   *
   * @param idleSpriteRegion
   *   The spritesheet region of the animation representing an idle machine.
   *
   * @param progressSpriteRegion
   *   The spritesheet region of the progress bar.
   *
   * @param drawRegion
   *   The region of the renderer where the machine will be drawn.
   *
   * @param factoryPoint
   *   The factory coordinates of the machine.
   *
   * @param busyDelay
   *   The number of ticks the machine will be busy.
   */
  StructureMachine(SDL_Texture *const spritesheet, SDL_Rect busySpriteRegion,
                   SDL_Rect idleSpriteRegion, SDL_Rect progressSpriteRegion,
                   SDL_Rect drawRegion, SDL_Point factoryPoint,
                   unsigned int busyDelay);

  /**
   * `Draw`
   *
   *   Draws the machine on the given renderer.
   */
  void Draw(SDL_Renderer *sdlRenderer);

  /**
   * `SetDrawPoint`
   *
   *   Sets the draw coordinates of the machine on the renderer.
   */
  void SetDrawPoint(const int x, const int y);

protected:
  /**
   * `OnUpdate`
   *
   *   Event when the machine is being updated.
   */
  void OnUpdate(unsigned int dt);

private:
  /**
   * `IsIdleChanged`
   *
   *   Handles the idle changed event.
   */
  void IsIdleChanged(EventPayload<Machine> &payload);
};

#endif
