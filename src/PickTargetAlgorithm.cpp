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
                         SDL_Point, std::vector<StructureMachine *>>(
          resultCallback),
      getNeighbors(getNeighborsCallback),
      searchPath(new SearchPathAlgorithm(
          [this](std::vector<SDL_Point> &path) { this->ReceivePath(path); },
          getNeighborsCallback)) {}

PickTargetAlgorithm::~PickTargetAlgorithm() { delete searchPath; }

bool PickTargetAlgorithm::Begin(SDL_Point origin,
                                std::list<StructureMachine *> candidates) {
  originArg = origin;
  candidatesArg = candidates;
  result.first = NULL;
  result.second.clear();
  if (candidatesArg.empty())
    return false;
  return searchPath->Begin(originArg,
                           candidatesArg.back()->GetFactoryPoint()) ||
         !candidatesArg.empty();
}

bool PickTargetAlgorithm::Next() {
  return searchPath->Next() || !candidatesArg.empty();
}

void PickTargetAlgorithm::ReceivePath(std::vector<SDL_Point> &path) {
  if (result.second.empty() ||
      (!path.empty() && path.size() < result.second.size())) {
    result.first = candidatesArg.back();
    result.second = path;
  }
  candidatesArg.pop_back();
  if (candidatesArg.empty())
    Return(result);
  else
    searchPath->Begin(originArg, candidatesArg.back()->GetFactoryPoint());
}
