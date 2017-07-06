/*******************************************************************************
@file `PickTargetAlgorithm.cpp`
  Created July 5, 2017

@author CJ Dimaano
  <c.j.s.dimaano@gmail.com>
*******************************************************************************/

#include "PickTargetAlgorithm.h"

PickTargetAlgorithm::PickTargetAlgorithm(
    std::function<void(std::pair<StructureMachine *, std::vector<SDL_Point>> &)>
        resultCallback,
    std::function<std::vector<SDL_Point>(SDL_Point)> getNeighborsCallback)
    : IterativeAlgorithm<std::pair<StructureMachine *, std::vector<SDL_Point>>,
                         SDL_Point, std::vector<SDL_Point>>(resultCallback),
      nextFn(&PickTargetAlgorithm::Noop),
      searchPath(std::bind(&PickTargetAlgorithm::ReceivePath, this,
                           std::vector<SDL_Point>()),
                 getNeighborsCallback) {}

bool PickTargetAlgorithm::Begin(SDL_Point origin,
                                std::vector<StructureMachine *> candidates) {
  originArg = origin;
  candidatesArg = candidates;
  result.first = NULL;
  result.second.clear();
  if (candidatesArg.empty())
    nextFn = &PickTargetAlgorithm::Noop;
  else
    nextFn = std::bind(&SearchPathAlgorithm::Next, &searchPath);
  searchPath.Begin(originArg, candidatesArg.back()->GetFactoryPoint());
  return Next();
}

bool PickTargetAlgorithm::Next() { return nextFn() || !candidatesArg.empty(); }

void PickTargetAlgorithm::ReceivePath(std::vector<SDL_Point> &path) {
  if (result.second.empty() || path.size() < result.second.size()) {
    result.first = candidatesArg.back();
    result.second = path;
  }
  candidatesArg.pop_back();
  if (candidatesArg.empty()) {
    nextFn = &PickTargetAlgorithm::Noop;
    Return(result);
  } else {
    nextFn = std::bind(&SearchPathAlgorithm::Next, &searchPath);
    searchPath.Begin(originArg, candidatesArg.back()->GetFactoryPoint());
  }
}
