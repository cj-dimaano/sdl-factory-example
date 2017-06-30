/*******************************************************************************
@file `Machine.h`
  Created June 28, 2017

@author CJ Dimaano
  <c.j.s.dimaano@gmail.com>
*******************************************************************************/

#ifndef MACHINE_H
#define MACHINE_H

#include "AnimatedSprite.h"
#include <SDL2/SDL.h>

/**
 * `Machine`
 *
 *   Abstract class for machines. Provides general functionality.
 */
class Machine {

  /**
   * `_busyDelay`
   *
   *   The number of ticks the machine will be busy.
   */
  unsigned int _busyDelay;

  /**
   * `_busyTick`
   *
   *   The number of ticks that has passed since it started being busy.
   */
  unsigned int _busyTick;

  /**
   * `_factoryPoint`
   *
   *   Factory coordinates of the machine.
   */
  SDL_Point _factoryPoint;

  /**
   * `_sprite`
   *
   *   The machine sprite.
   */
  AnimatedSprite _sprite;

  /**
   * `_isPaused`
   *
   *   True if the machine has suspended work; otherwise, false.
   */
  bool _isPaused;

public:
  /**
   * `Machine`
   *
   *   Constructor.
   *
   * @param sprite
   *   The animated sprite of the machine.
   *
   * @param factoryPoint
   *   The factory coordinates of the machine.
   *
   * @param busyDelay
   *   The number of ticks the machine will be busy.
   */
  Machine(AnimatedSprite sprite, SDL_Point factoryPoint,
          unsigned int busyDelay);

  /**
   * `~Machine`
   *
   *   Destructor.
   */
  virtual ~Machine() {}

  /**
   * `Update`
   *
   *   Updates the machine.
   */
  void Update(unsigned int dt);

  /**
   * `Draw`
   *
   *   Draws the machine on the given renderer.
   */
  virtual void Draw(SDL_Renderer *sdlRenderer) = 0;

  /**
   * `IsReady`
   *
   *   True if the machine is ready for work; otherwise, false.
   */
  bool IsReady();

  /**
   * `Start`
   *
   *   Signals the machine to start working.
   */
  void Start();

  /**
   * `Pause`
   *
   *   Signals the machine to suspend working.
   */
  void Pause();

  /**
   * `Restart`
   *
   *   Signals the machine to restart working.
   */
  void Restart();

  /**
   * `Reset`
   *
   *   Signals the machine to reset work progress.
   */
  void Reset();

  /**
   * `GetProgress`
   *
   *   Gets the work progress of the machine between 0 and 100, inclusive.
   */
  unsigned int GetProgress();

  /**
   * `GetFactoryPoint`
   *
   *   Gets a reference to the factory coordinates of the machine.
   */
  SDL_Point &GetFactoryPoint();

  /**
   * `SetFactoryPoint`
   *
   *   Sets the factory coordinates of the machine.
   */
  void SetFactoryPoint(SDL_Point value);

  /**
   * `SetFactoryPoint`
   *
   *   Sets the factory coordinates of the machine.
   */
  void SetFactoryPoint(const int x, const int y);

  /**
   * `SetDrawPoint`
   *
   *   Sets the draw coordinates of the machine on the renderer.
   */
  virtual void SetDrawPoint(const int x, const int y);

  /**
   * `GetMachineSprite`
   *
   *   Gets the animated sprite of the machine.
   */
  AnimatedSprite &GetMachineSprite();

protected:
  /**
   * `OnUpdate`
   *
   *   Event when the machine is being updated.
   */
  virtual void OnUpdate(unsigned int) {}

  /**
   * `OnBusy`
   *
   *   Event when the machine changes from idle to busy.
   */
  virtual void OnBusy(){}

  /**
   * `OnIdle`
   *
   *   Event when the machine changes from busy to idle.
   */
  virtual void OnIdle(){}
};

#endif
