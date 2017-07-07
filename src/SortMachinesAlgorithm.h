/*******************************************************************************
@file `SortMachinesAlgorithm.h`
  Created June 30, 2017

@author CJ Dimaano
  <c.j.s.dimaano@gmail.com>
*******************************************************************************/

#pragma once

#include "IterativeAlgorithm.h"
#include "Machine.h"
#include <SDL2/SDL.h>
#include <functional>
#include <vector>

/**
 * `SortMachinesAlgorithm`
 *
 *   Sorts a collection of machines based on distance using the heapsort
 *   algorithm.
 */
class SortMachinesAlgorithm
    : public IterativeAlgorithm<std::vector<Machine *>, std::vector<Machine *>,
                                SDL_Point> {

  /**
   * `nextFn`
   *
   *   Pointer to the next function.
   */
  // void *(SortMachinesAlgorithm::*nextFn)();
  std::function<bool()> nextFn;

  int i;
  int j;
  int k;
  Machine *val;
  int valDist;
  int end;
  SDL_Point argOrigin;
  std::vector<Machine *> argMachines;

public:
  /**
   * `SortMachinesAlgorithm`
   *
   *   Constructor.
   *
   * @param resultCallback
   *   The callback to be called when the result of the algorithm is ready.
   */
  SortMachinesAlgorithm(
      std::function<void(std::vector<Machine *> &)> resultCallback)
      : IterativeAlgorithm<std::vector<Machine *>, std::vector<Machine *>,
                           SDL_Point>(resultCallback),
        i(0), j(0), k(0), val(NULL), valDist(0), end(0), argOrigin(),
        argMachines(), nextFn([]() { return false; }) {}

  /**
   * `Begin`
   *
   *   Begins the algorithm for iterative execution.
   *
   * @returns
   *   True if there is a next iteration; otherwise, false.
   */
  bool Begin(std::vector<Machine *> machines, SDL_Point origin);

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
  bool Loop1Begin();
  bool Loop1End();
  bool Loop2Begin();
  bool Loop2End();
  bool Loop3();
};
