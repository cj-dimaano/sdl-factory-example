/*******************************************************************************
@file `IterativeState.h`
  Created June 30, 2017

@author CJ Dimaano
  <c.j.s.dimaano@gmail.com>
*******************************************************************************/

#ifndef ITERATIVESTATE_H
#define ITERATIVESTATE_H

/**
 * `IterativeState`
 *
 *   Houses the state of an iterative algorithm.
 *
 * @param R
 *   The result type of the iterative algorithm.
 */
template <typename R> class IterativeState {

  /**
   * `result`
   *
   *   The result of the iterative algorithm.
   */
  R result;

public:
  /**
   * `~IterativeState`
   *
   *   Virtual destructor.
   */
  virtual ~IterativeState() {}

  /**
   * `GetResult`
   *
   *   Gets the result of the iterative algorithm.
   */
  R GetResult() { return result; }

  /**
   * `SetResult`
   *
   *   Sets the result of the iterative algorithm.
   */
  void SetResult(R value) { result = value; }
};

#endif
