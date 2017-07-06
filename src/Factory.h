/*******************************************************************************
@file `Factory.h`
  Created June 28, 2017

@author CJ Dimaano
  <c.j.s.dimaano@gmail.com>
*******************************************************************************/

#pragma once

#include "ConsumerMachine.h"
#include "ProducerMachine.h"
#include "RobotMachine.h"
#include "Sprite.h"
#include <SDL2/SDL.h>
#include <vector>

/**
 * `Factory`
 *
 *   Represents the factory map.
 */
class Factory {

  /**
   * `spritesheet`
   *
   *   The spritesheet for the factory.
   */
  SDL_Texture *spritesheet;

  /**
   * `drawPoint`
   *
   *   The top-left pixel of the factory map.
   */
  SDL_Point drawPoint;

  /**
   * `factorySize`
   *
   *   The height and width of the factory in factory tiles.
   */
  SDL_Point factorySize;

  /**
   * `tile`
   *
   *   The tile sprite.
   */
  Sprite tile;

  /**
   * `consumers`
   *
   *   The set of consumer machines.
   */
  std::vector<ConsumerMachine> consumers;

  /**
   * `candidateConsumers`
   *
   *   Candidate target consumer machines.
   */
  std::vector<StructureMachine *> candidateConsumers;

  /**
   * `producers`
   *
   *   The set of producer machines.
   */
  std::vector<ProducerMachine> producers;

  /**
   * `candidateProducers`
   *
   *   Candidate target producer machines.
   */
   std::vector<StructureMachine *> candidateProducers;

  /**
   * `robots`
   *
   *   The set of robot machines.
   */
  std::vector<RobotMachine> robots;

public:
  /**
   * `Factory`
   *
   *   Constructor.
   *
   * @param factorySpritesheet
   *   The SDL texture containing the factory sprites.
   *
   * @param x
   *   The x-coordinate of the screen where the factory will be drawn.
   *
   * @param y
   *   The y-coordinate of the screen where the factory will be drawn.
   *
   * @param width
   *   The tile width of the factory.
   *
   * @param height
   *   The tile height of the factory.
   */
  Factory(SDL_Texture *factorySpritesheet, int x, int y, int width, int height);

  /**
   * `Update`
   *
   *   Updates the factory.
   *
   * @param dt
   *   The change in ticks since the last update.
   */
  void Update(unsigned int dt);

  /**
   * `Draw`
   *
   *   Draws the factory on the given renderer.
   */
  void Draw(SDL_Renderer *sdlRenderer);

  /**
   * `AddConsumerMachine`
   *
   *   Adds a consumer machine to the factory at the given factory coordinate.
   */
  void AddConsumerMachine(int x, int y);

  /**
   * `AddProducerMachine`
   *
   *   Adds a producer machine to the factory at the given factory coordinate.
   */
  void AddProducerMachine(int x, int y);

  /**
   * `AddRobotMachine`
   *
   *   Adds a robot machine to the factory at the given factory coordinate.
   */
  void AddRobotMachine(int x, int y);

private:
  /**
   * `HasTargetChanged`
   *
   *   Handles the target changed event.
   */
  void HasTargetChanged(EventPayload<RobotMachine> &payload);

  /**
   * `ConsumerIsIdleChanged`
   *
   *   Handles the idle changed event for consumers.
   */
  void ConsumerIsIdleChanged(EventPayload<Machine> &payload);

  /**
   * `ProducerIsIdleChanged`
   *
   *   Handles the idle changed event for producers.
   */
  void ProducerIsIdleChanged(EventPayload<Machine> &payload);
};
