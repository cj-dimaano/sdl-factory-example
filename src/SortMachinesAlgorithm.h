/*******************************************************************************
@file `SortMachinesAlgorithm.h`
  Created June 30, 2017

@author CJ Dimaano
  <c.j.s.dimaano@gmail.com>
*******************************************************************************/

#ifndef SORTMACHINESALGORITHM_H
#define SORTMACHINESALGORITHM_H

#include "IterativeAlgorithm.h"
#include "SortMachinesState.h"

/**
 * `SortMachinesAlgorithm`
 *
 *   Sorts a collection of machines based on distance using the heapsort
 *   algorithm.
 */
class SortMachinesAlgorithm : public IterativeAlgorithm<SortMachinesState> {

  /**
   * `nextFn`
   *
   *   Pointer to the next function.
   */
  void *(*nextFn)(SortMachinesState &);

public:
  /**
   * `Begin`
   *
   *   Begins the algorithm for iterative execution.
   *
   * @returns
   *   True if there is a next iteration; otherwise, false.
   */
  bool Begin();

  /**
   * `Next`
   *
   *   Executes the next iteration of the algorithm.
   *
   * @returns
   *   True if there is a next iteration; otherwise, false.
   */
  bool Next();

protected:
};

#endif
