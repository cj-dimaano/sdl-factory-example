/*******************************************************************************
@file `RobotMachine.h`
  Created June 29, 2017

@author CJ Dimaano
  <c.j.s.dimaano@gmail.com>
*******************************************************************************/

#pragma once

#include "Events.h"
#include "Machine.h"
#include "PickTargetAlgorithm.h"
#include "StructureMachine.h"
#include <SDL2/SDL.h>
#include <functional>
#include <utility>
#include <vector>

/**
 * `RobotMachine`
 *
 *   Represents a robot machine in a factory.
 */
class RobotMachine : public Machine, private EventEmitter<RobotMachine> {

  /**
   * `_stepDelay`
   *
   *   The number of ticks required for the robot to make a full step.
   */
  unsigned int _stepDelay;

  /**
   * `_stepTick`
   *
   *   The number of ticks that have passed since the previous step.
   */
  unsigned int _stepTick;

  /**
   * `_isEmpty`
   *
   *   Whether or not the robot is carrying a payload.
   */
  bool _isEmpty;

  /**
   * `_isPickingTarget`
   *
   *   Whether or not the robot is currently searching for a target.
   */
  bool _isPickingTarget;

  /**
   * `_emptySpriteRegion`
   *
   *   The region of the sprite sheet for the empty robot.
   */
  SDL_Rect _emptySpriteRegion;

  /**
   * `_fullSpriteRegion`
   *
   *   The region of the sprite sheet for the loaded robot.
   */
  SDL_Rect _fullSpriteRegion;

  /**
   * `_path`
   *
   *   The stack of points representing the path from the robot to the target.
   */
  std::vector<SDL_Point> _path;

  /**
   * `_target`
   *
   *   The current target of the robot.
   */
  StructureMachine *_target;

  /**
   * `_pickTarget`
   *
   *   Picks a target from a collection of candidates.
   */
  PickTargetAlgorithm *_pickTarget;

public:
  /**
   * `RobotMachine`
   *
   *   Constructor.
   *
   * @param spritesheet
   *   The SDL texture containing the sprites.
   *
   * @param drawRegion
   *   The region of the renderer on which to draw the sprite.
   *
   * @param factoryPoint
   *   The factory coordinates of the machine.
   */
  RobotMachine(SDL_Texture *spritesheet, SDL_Rect drawRegion,
               SDL_Point factoryPoint);

  /**
   * `~RobotMachine`
   *
   *   Destructor.
   */
  ~RobotMachine();

  /**
   * `AddHasTargetChangedEventHandler`
   *
   *   Adds an event handler for the `HasTargetChanged` event.
   */
  void AddHasTargetChangedEventHandler(
      std::function<void(EventPayload<RobotMachine> &)> handler);

  /**
   * `PickTarget`
   *
   *   Selects the nearest target from a collection of candidate structure
   *   machines.
   *
   * @description
   *   The shortest path is calculated for each candidate. The candidate with
   *   the shortest path is chosen as the target.
   *
   *   It is recommended that the factory recall this method if the collection
   *   of candidates changes.
   */
  void PickTarget(std::vector<StructureMachine *> candidates);

  /**
   * `GetTarget`
   *
   *   Gets the current target of the robot.
   */
  StructureMachine *GetTarget() { return _target; }

  /**
   * `HasTarget`
   *
   *   True if the robot has a target; otherwise, false.
   */
  bool HasTarget() { return _target != NULL; }

  /**
   * `IsEmpty`
   *
   *   True if the robot is emptyhanded; otherwise, false.
   */
  bool IsEmpty() { return _isEmpty; }

  /**
   * `IsPickingTarget`
   *
   *   True if the robot is searching for a target; otherwise, false.
   */
  bool IsPickingTarget() { return _isPickingTarget; }

  /**
   * `GetStepProgress`
   *
   *   Gets a value between 0 and 1 indicating how much progress towards the
   *   next step the robot has made.
   */
  double GetStepProgress() {
    return static_cast<double>(_stepTick) / static_cast<double>(_stepDelay);
  }

  /**
   * `GetStep`
   *
   *   Gets the factory coordinate of the current step.
   */
  SDL_Point GetStep() {
    return _path.empty() ? GetFactoryPoint() : _path.back();
  }

protected:
  /**
   * `OnHasTargetChanged`
   *
   *   Event when the machine changes its target.
   */
  virtual void OnHasTargetChanged();

  /**
   * `OnUpdate`
   *
   *   Event when the machine is being updated.
   */
  void OnUpdate(unsigned int dt);

private:
  /**
   * `SetTargetPath`
   *
   *   Callback for the pick target algorithm.
   */
  void SetTargetPath(
      std::pair<StructureMachine *, std::vector<SDL_Point>> &targetPath);

  /**
   * `IsIdleChanged`
   *
   *   Handles the IsIdleChanged event.
   */
  void IsIdleChanged(EventPayload<Machine> &payload);
};
