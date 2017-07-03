/*******************************************************************************
@file `SortMachinesAlgorithm.cpp`
  Created June 30, 2017

@author CJ Dimaano
  <c.j.s.dimaano@gmail.com>
*******************************************************************************/

#include "SortMachinesAlgorithm.h"

/**
 * `PI`
 *
 *   Parent Index.
 */
#define PI(x) (((x)-1) >> 1)

bool SortMachinesAlgorithm::Begin(std::vector<Machine *> machines,
                                  SDL_Point origin) {
  argMachines = machines;
  argOrigin = origin;
  end = machines.size();
  return Loop1Begin();
}

bool SortMachinesAlgorithm::Next() { return nextFn(); }

bool SortMachinesAlgorithm::Loop1Begin() {
  if (end > 0) {
    i = 1;
    return Loop2Begin();
  }
  Return(argMachines);
  nextFn = &SortMachinesAlgorithm::Noop;
  return false;
}

bool SortMachinesAlgorithm::Loop1End() {
  Machine *swap = argMachines[end - 1];
  argMachines[end - 1] = argMachines[0];
  argMachines[0] = swap;
  end--;
  nextFn = std::bind(&SortMachinesAlgorithm::Loop1Begin, this);
  return true;
}

bool SortMachinesAlgorithm::Loop2Begin() {
  if (i < end) {
    val = argMachines[i];
    SDL_Point p = val->GetFactoryPoint();
    int x = argOrigin.x - p.x;
    int y = argOrigin.y - p.y;
    valDist = x * x + y * y;
    j = i;
    return Loop3();
  }
  return Loop1End();
}

bool SortMachinesAlgorithm::Loop2End() {
  argMachines[j] = val;
  i++;
  nextFn = std::bind(&SortMachinesAlgorithm::Loop2Begin, this);
  return true;
}

bool SortMachinesAlgorithm::Loop3() {
  if (j > 0) {
    k = PI(j);
    SDL_Point p = argMachines[k]->GetFactoryPoint();
    int x = argOrigin.x - p.x;
    int y = argOrigin.y - p.y;
    if (valDist > x * x + y * y) {
      Machine *swap = argMachines[j];
      argMachines[j] = argMachines[k];
      argMachines[k] = swap;
      j = k;
      // nextFn = &SortMachinesAlgorithm::Loop3;
      return true;
    }
  }
  return Loop2End();
}
