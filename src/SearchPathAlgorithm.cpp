/*******************************************************************************
@file `SearchPathAlgorithm.cpp`
  Created July 2, 2017

@author CJ Dimaano
  <c.j.s.dimaano@gmail.com>
*******************************************************************************/

#include "SearchPathAlgorithm.h"

std::size_t SearchPathAlgorithm::SDL_PointHash::
operator()(const SDL_Point value) const {
  std::size_t result = static_cast<std::size_t>(value.x);
  result *= 2654435761U;
  return result ^ static_cast<std::size_t>(value.y);
}

bool SearchPathAlgorithm::SDL_PointCompare::
operator()(const SDL_Point lhs, const SDL_Point rhs) const {
  return owner.CalcFScore(lhs) > owner.CalcFScore(rhs);
}

bool SearchPathAlgorithm::SDL_PointEqual::
operator()(const SDL_Point lhs, const SDL_Point rhs) const {
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

SearchPathAlgorithm::SearchPathAlgorithm(
    std::function<void(std::vector<SDL_Point> &)> resultCallback,
    std::function<std::vector<SDL_Point>(SDL_Point)> getNeighborsFn)
    : IterativeAlgorithm<std::vector<SDL_Point>, SDL_Point, SDL_Point>(
          resultCallback),
      getNeighbors(getNeighborsFn), nextFn(&loops[0]), openQueue(*this) {
  loops[0] = [this]() { return false; };
  loops[1] = [this]() {
    if (openQueue.empty()) {
      result.clear();
      nextFn = &loops[0];
      Return(result);
      return (*nextFn)();
    }
    current = openQueue.top();
    if (SDL_PointEqual()(current, argGoal)) {
      result.clear();
      result.push_back(current);
      nextFn = &loops[3];
      return (*nextFn)();
    }
    openQueue.pop();
    openSet.erase(current);
    closedSet.insert(current);
    neighbors = getNeighbors(current);
    if (neighbors.empty())
      return true;
    i = 0;
    nextFn = &loops[2];
    return (*nextFn)();
  };
  loops[2] = [this]() {
    if (i >= neighbors.size()) {
      nextFn = &loops[1];
      return true;
    }
    SDL_Point &neighbor = neighbors[i];
    auto search = closedSet.find(neighbor);
    if (search != closedSet.end()) {
      i++;
      return true;
    }
    if (openSet.insert(neighbor).second)
      openQueue.push(neighbor);
    // Assume there is a gScore for current.
    int score = gScore[current] + CalcDist(current, neighbor);
    auto gScoreNeighbor = gScore.find(neighbor);
    if (gScoreNeighbor != gScore.end() && gScoreNeighbor->second < score) {
      i++;
      return true;
    }
    cameFrom[neighbor] = current;
    gScore[neighbor] = score;
    fScore[neighbor] = CalcFScore(neighbor);
    i++;
    return true;
  };
  loops[3] = [this]() {
    auto search = cameFrom.find(current);
    if (search != cameFrom.end()) {
      current = search->second;
      result.push_back(current);
      search = cameFrom.find(current);
      return true;
    }
    nextFn = &loops[0];
    Return(result);
    return (*nextFn)();
  };
}

int SearchPathAlgorithm::CalcFScore(const SDL_Point p) const {
  return CalcDist(p, argGoal);
}

int SearchPathAlgorithm::CalcDist(const SDL_Point a, const SDL_Point b) const {
  int x = a.x - b.x;
  int y = a.y - b.y;
  return x * x + y * y;
}

bool SearchPathAlgorithm::Begin(SDL_Point start, SDL_Point goal) {
  argStart = start;
  argGoal = goal;
  openQueue.clear();
  openSet.clear();
  closedSet.clear();
  cameFrom.clear();
  gScore.clear();
  fScore.clear();
  openQueue.push(argStart);
  openSet.insert(argStart);
  gScore[argStart] = 0;
  fScore[argStart] = CalcFScore(argStart);
  nextFn = &loops[1];
  return (*nextFn)();
}
