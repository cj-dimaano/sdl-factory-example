/*******************************************************************************
@file `PickTargetAlgorithm.h`
  Created July 5, 2017

@author CJ Dimaano
  <c.j.s.dimaano@gmail.com>
*******************************************************************************/

#ifndef PICKTARGETALGORITHM_H
#define PICKTARGETALGORITHM_H

#include "IterativeAlgorithm.h"
#include "SearchPathAlgorithm.h"
#include "StructureMachine.h"
#include <SDL2/SDL.h>
#include <functional>
#include <utility>
#include <vector>

/**
 * `PickTargetAlgorithm`
 *
 *   Picks a target with the shortest path from a given set of candidates.
 */
class PickTargetAlgorithm
    : public IterativeAlgorithm<
          std::pair<StructureMachine *, std::vector<SDL_Point>>, SDL_Point,
          std::vector<SDL_Point>> {

  /**
   * `nextFn`
   *
   *   The function to be called on the next iteration.
   */
  std::function<bool()> nextFn;

  /**
   * `result`
   *
   *   The result of the algorithm.
   */
  std::pair<StructureMachine *, std::vector<SDL_Point>> result;

  /**
   * `candidatesArg`
   *
   *   The collection of candidate machines from which to choose.
   */
  std::vector<StructureMachine *> candidatesArg;

  /**
   * `originArg`
   *
   *   The origin point to be calculated for each candidate machine.
   */
  SDL_Point originArg;

  /**
   * `searchPath`
   *
   *   The search path algorithm for calculating the path from the origin to
   *   each machine.
   */
  SearchPathAlgorithm searchPath;

public:
  /**
   * `PickTargetAlgorithm`
   *
   *   Constructor.
   *
   * @param resultCallback
   *   The function to be called when the result is ready. The result is a pair
   *   containing a machine with its associated path.
   *
   * @param getNeighborsCallback
   *   The function that returns valid neighbors from a given point.
   */
  PickTargetAlgorithm(
      std::function<
          void(std::pair<StructureMachine *, std::vector<SDL_Point>> &)>
          resultCallback,
      std::function<std::vector<SDL_Point>(SDL_Point)> getNeighborsCallback);

  /**
   * `Begin`
   *
   *   Begins the algorithm for iterative execution.
   *
   * @returns
   *   True if there is a next iteration; otherwise, false.
   */
  bool Begin(SDL_Point origin, std::vector<StructureMachine *> candidates);

  /**
   * `Next`
   *
   *   Executes the next iteration of the algorithm.
   *
   * @returns
   *   True if there is a next iteration; otherwise, false.
   */
  bool Next();

private:
  static bool Noop() { return false; }
  void ReceivePath(std::vector<SDL_Point> &path);
};

#endif
