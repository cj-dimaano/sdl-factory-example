/*******************************************************************************
@file `SortMachinesState.h`
  Created June 30, 2017

@author CJ Dimaano
  <c.j.s.dimaano@gmail.com>
*******************************************************************************/

#ifndef SORTMACHINESSTATE_H
#define SORTMACHINESSTATE_H

#include "IterativeState.h"
#include "Machine.h"
#include <SDL2/SDL.h>
#include <vector>

/**
 * `SortMachinesState`
 *
 *   Iterative state for sorting machines by distance.
 */
class SortMachinesState : public IterativeState<std::vector<Machine *> > {

public:
  /**
   * `SortMachinesState`
   *
   *   Constructor.
   */
  SortMachinesState()
      : origin(), machines(), i(0), j(0), k(0), val(NULL), valDist(0), end(0) {}

  int i;
  int j;
  int k;
  Machine *val;
  int valDist;
  int end;
  SDL_Point origin;
  std::vector<Machine *> machines;
};

#endif
