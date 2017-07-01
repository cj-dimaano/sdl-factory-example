/*******************************************************************************
@file `SortMachinesAlgorithm.cpp`
  Created June 30, 2017

@author CJ Dimaano
  <c.j.s.dimaano@gmail.com>
*******************************************************************************/

#include "SortMachinesAlgorithm.h"

/* Macros *********************************************************************/

/**
 * `PI`
 *
 *   Parent Index.
 */
#define PI(x) (((x)-1) >> 1)

/* Static function declarations ***********************************************/

static void *loop1Begin(SortMachinesState &);
static void *loop1End(SortMachinesState &);
static void *loop2Begin(SortMachinesState &);
static void *loop2End(SortMachinesState &);
static void *loop3(SortMachinesState &);

/* SortMachinesAlgorithm implementation ***************************************/

bool SortMachinesAlgorithm::Begin() {
  return (nextFn = reinterpret_cast<void *(*)(SortMachinesState &)>(
              loop1Begin(GetState()))) != NULL;
}

bool SortMachinesAlgorithm::Next() {
  return nextFn != NULL &&
         (nextFn = reinterpret_cast<void *(*)(SortMachinesState &)>(
              nextFn(GetState()))) != NULL;
}

/* Static function definitions ************************************************/

static void *loop1Begin(SortMachinesState &state) {
  if (state.end > 0) {
    state.i = 1;
    return loop2Begin(state);
  }
  state.SetResult(state.machines);
  return NULL;
}

static void *loop1End(SortMachinesState &state) {
  Machine *swap = state.machines[state.end - 1];
  state.machines[state.end - 1] = state.machines[0];
  state.machines[0] = swap;
  state.end--;
  return reinterpret_cast<void *>(&loop1Begin);
}

static void *loop2Begin(SortMachinesState &state) {
  if (state.i < state.end) {
    state.val = state.machines[state.i];
    SDL_Point p = state.val->GetFactoryPoint();
    int x = state.origin.x - p.x;
    int y = state.origin.y - p.y;
    state.valDist = x * x + y * y;
    state.j = state.i;
    return loop3(state);
  }
  return loop1End(state);
}

static void *loop2End(SortMachinesState &state) {
  state.machines[state.j] = state.val;
  state.i++;
  return reinterpret_cast<void *>(&loop2Begin);
}

static void *loop3(SortMachinesState &state) {
  if (state.j > 0) {
    state.k = PI(state.j);
    SDL_Point p = state.machines[state.k]->GetFactoryPoint();
    int x = state.origin.x - p.x;
    int y = state.origin.y - p.y;
    if (state.valDist > x * x + y * y) {
      Machine *swap = state.machines[state.j];
      state.machines[state.j] = state.machines[state.k];
      state.machines[state.k] = swap;
      state.j = state.k;
      return reinterpret_cast<void *>(&loop3);
    }
  }
  return loop2End(state);
}
