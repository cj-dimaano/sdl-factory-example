/*******************************************************************************
@file `IterativeAlgorithm.h`
  Created June 30, 2017

@author CJ Dimaano
  <c.j.s.dimaano@gmail.com>
*******************************************************************************/

#ifndef ITERATIVEALGORITHM_H
#define ITERATIVEALGORITHM_H

#include <functional>

/**
 * `IterativeAlgorithm`
 *
 *   Default class for defining an iterative algorithm.
 *
 * @description
 *   An iterative algorithm is an algorithm that contains a loop, such as a
 *   sorting algorithm. The `IterativeAlgorithm` class defines a set of methods
 *   to step through each iteration of the algorithm as if being executed
 *   through a loop.
 *
 *   The purpose of this class is to be used as part of the updating logic of a
 *   standard game loop, where each call to update executes the next step of the
 *   iterative algorithm. This is particularly useful for game objects that need
 *   to process data in an iterative manner, such as calculating the shortest
 *   path.
 */
template <class R, class... Args> class IterativeAlgorithm {

  /**
   * `_resultCallback`
   *
   *   The function to be called when the result is ready.
   */
  std::function<void(R &)> _resultCallback;

public:
  /**
   * `IterativeAlgorithm`
   *
   *   Constructor.
   *
   * @param resultCallback
   *   The function to be called when the result is ready.
   */
  IterativeAlgorithm(std::function<void(R &)> resultCallback)
      : _resultCallback(resultCallback) {}

  /**
   * `~IterativeAlgorithm`
   *
   *   Virtual destructor.
   */
  virtual ~IterativeAlgorithm() {}

  /**
   * `Begin`
   *
   *   Begins the algorithm for iterative execution.
   *
   * @returns
   *   True if there is a next iteration; otherwise, false.
   */
  virtual bool Begin(Args... args) { return false; }

  /**
   * `Next`
   *
   *   Executes the next iteration of the algorithm.
   *
   * @returns
   *   True if there is a next iteration; otherwise, false.
   */
  virtual bool Next() { return false; }

protected:
  /**
   * `Return`
   *
   *   Returns the result to the caller.
   */
  void Return(R result) { _resultCallback(result); }
};

#endif
