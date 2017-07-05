/*******************************************************************************
@file `SearchPathAlgorithm.cpp`
  Created July 2, 2017

@author CJ Dimaano
  <c.j.s.dimaano@gmail.com>
*******************************************************************************/

#include "SearchPathAlgorithm.h"

std::size_t SearchPathAlgorithm::SDL_PointHash::
operator()(SDL_Point const &value) const {
  std::size_t result = static_cast<std::size_t>(value.x);
  result *= 2654435761U;
  return result ^ static_cast<std::size_t>(value.y);
}

bool SearchPathAlgorithm::SDL_PointCompare::
operator()(const SDL_Point &lhs, const SDL_Point &rhs) const {
  return owner.CalcFScore(lhs) > owner.CalcFScore(rhs);
}

bool SearchPathAlgorithm::SDL_PointEqual::
operator()(const SDL_Point &lhs, const SDL_Point &rhs) const {
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

int SearchPathAlgorithm::CalcFScore(const SDL_Point p) const {
  return CalcDist(p, argGoal);
}

int SearchPathAlgorithm::CalcDist(const SDL_Point a, const SDL_Point b) const {
  int x = a.x - b.x;
  int y = a.y - b.y;
  return x * x + y * y;
}

bool SearchPathAlgorithm::SearchLoop1() {
  if (!openQueue.empty()) {
    current = openQueue.top();
    if (SDL_PointEqual()(current, argGoal)) {
      result.clear();
      result.push_back(current);
      nextFn = std::bind(&SearchPathAlgorithm::ReconstructPath, this);
      return true;
    }
    openQueue.pop();
    openSet.erase(current);
    closedSet.insert(current);
    neighbors = getNeighbors(current);
    if (neighbors.empty())
      return true;
    it = neighbors.begin();
    nextFn = std::bind(&SearchPathAlgorithm::SearchLoop2, this);
    return nextFn();
  }
  result.clear();
  Return(result);
  nextFn = &SearchPathAlgorithm::Noop;
  return false;
}

bool SearchPathAlgorithm::SearchLoop2() {
  if (it == neighbors.end()) {
    nextFn = std::bind(&SearchPathAlgorithm::SearchLoop1, this);
    return true;
  }
  auto search = closedSet.find(*it);
  if (search != closedSet.end()) {
    it = std::next(it);
    return true;
  }
  if (openSet.insert(*it).second)
    openQueue.push(*it);
  // Assume there is a gScore for current.
  int score = gScore[current] + CalcDist(current, *it);
  auto gScoreNeighbor = gScore.find(*it);
  if (gScoreNeighbor != gScore.end() && gScoreNeighbor->second < score) {
    it = std::next(it);
    return true;
  }
  cameFrom[*it] = current;
  gScore[*it] = score;
  fScore[*it] = CalcFScore(*it);
  it = std::next(it);
  return true;
}

bool SearchPathAlgorithm::ReconstructPath() {
  auto search = cameFrom.find(current);
  if (search != cameFrom.end()) {
    current = search->second;
    result.push_back(current);
    search = cameFrom.find(current);
    return true;
  }
  Return(result);
  nextFn = &SearchPathAlgorithm::Noop;
  return false;
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
  gScore.insert(std::make_pair(argStart, 0));
  fScore.insert(std::make_pair(argStart, CalcFScore(argStart)));
  nextFn = std::bind(&SearchPathAlgorithm::SearchLoop1, this);
  return nextFn();
}
