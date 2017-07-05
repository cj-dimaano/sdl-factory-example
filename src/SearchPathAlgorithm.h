/*******************************************************************************
@file `SearchPathAlgorithm.h`
  Created July 1, 2017

@author CJ Dimaano
  <c.j.s.dimaano@gmail.com>
*******************************************************************************/

#ifndef SEARCHPATHALGORITHM_H
#define SEARCHPATHALGORITHM_H

#include "IterativeAlgorithm.h"
#include <SDL2/SDL.h>
#include <functional>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/**
 * `SearchPathAlgorithm`
 *
 *   Uses a modified A* algorithm to calculate the shortest path between two
 *   points.
 *
 * @description
 *   The algorithm makes a couple of assumptions; namely, that the cost from
 *   traversing between neighboring points is the same for all points, and that
 *   the target point is reachable from anywhere on the map.
 *
 *   The heuristic cost from each point to the target point is simply the
 *   distance between the two points (without calculating the square root).
 */
class SearchPathAlgorithm
    : public IterativeAlgorithm<std::vector<SDL_Point>, SDL_Point, SDL_Point> {
  struct SDL_PointHash {
    std::size_t operator()(SDL_Point const &value) const;
  };
  struct SDL_PointCompare {
    SDL_PointCompare(const SearchPathAlgorithm &ownerAlgorithm)
        : owner(ownerAlgorithm) {}
    bool operator()(const SDL_Point &lhs, const SDL_Point &rhs) const;
    const SearchPathAlgorithm &owner;
  };
  struct SDL_PointEqual {
    bool operator()(const SDL_Point &lhs, const SDL_Point &rhs) const;
  };
  struct PriorityQueue
      : public std::priority_queue<SDL_Point, std::vector<SDL_Point>,
                                   SearchPathAlgorithm::SDL_PointCompare> {
    PriorityQueue(const SearchPathAlgorithm &owner)
        : std::priority_queue<SDL_Point, std::vector<SDL_Point>,
                              SearchPathAlgorithm::SDL_PointCompare>(
              SDL_PointCompare(owner)) {}
    void clear() { this->c.clear(); }
  };
  using PointVector = std::vector<SDL_Point>;
  using PointSet =
      std::unordered_set<SDL_Point, SearchPathAlgorithm::SDL_PointHash,
                         SearchPathAlgorithm::SDL_PointEqual>;
  template <class V>
  using PointMap =
      std::unordered_map<SDL_Point, V, SearchPathAlgorithm::SDL_PointHash,
                         SearchPathAlgorithm::SDL_PointEqual>;

  /**
   * `nextFn`
   *
   *   The next function to be called.
   */
  std::function<bool()> nextFn;

  /**
   * `getNeighbors`
   *
   *   Gets the neighboring nodes from a given point.
   */
  std::function<std::vector<SDL_Point>(SDL_Point)> getNeighbors;

  SDL_Point argStart;
  SDL_Point argGoal;
  PriorityQueue openQueue;
  PointSet openSet;
  PointSet closedSet;
  PointMap<SDL_Point> cameFrom;
  PointMap<unsigned int> gScore;
  PointMap<unsigned int> fScore;
  SDL_Point current;
  PointVector neighbors;
  PointVector::iterator it;
  PointVector result;

public:
  /**
   * `SearchPathAlgorithm`
   *
   *   Constructor.
   *
   * @param resultCallback
   *   Callback for the result of the algorithm.
   *
   * @param getNeighborsFn
   *   Function that returns the collection of neighboring points from a given
   *   point.
   */
  SearchPathAlgorithm(
      std::function<void(std::vector<SDL_Point> &)> resultCallback,
      std::function<std::vector<SDL_Point>(SDL_Point)> getNeighborsFn)
      : IterativeAlgorithm<std::vector<SDL_Point>, SDL_Point, SDL_Point>(
            resultCallback),
        getNeighbors(getNeighborsFn), nextFn(&SearchPathAlgorithm::Noop),
        openQueue(*this) {}

  /**
   * `Begin`
   *
   *   Begins the algorithm for iterative execution.
   *
   * @returns
   *   True if there is a next iteration; otherwise, false.
   */
  bool Begin(SDL_Point start, SDL_Point goal);

  /**
   * `Next`
   *
   *   Executes the next iteration of the algorithm.
   *
   * @returns
   *   True if there is a next iteration; otherwise, false.
   */
  bool Next() { return nextFn(); }

  /**
   * `CalcFScore`
   *
   *   Calculates the f-score for the given point.
   */
  int CalcFScore(const SDL_Point p) const;

private:
  static bool Noop() { return false; }
  int CalcDist(const SDL_Point a, const SDL_Point b) const;
  bool SearchLoop1();
  bool SearchLoop2();
  bool ReconstructPath();
};

#endif
