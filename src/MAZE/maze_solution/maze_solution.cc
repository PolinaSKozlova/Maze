#include "maze_solution.h"

#include <array>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>

#include "../maze_struct.h"

namespace maze {
void MazeSolution::FindPath(const Coordinate& start, const Coordinate& end) {
  std::set<Coordinate> visited;
  std::queue<Coordinate> current_cell;
  std::map<Coordinate, Coordinate> steps;

  current_cell.push(start);
  visited.insert(start);

  while (!current_cell.empty()) {
    Coordinate current = current_cell.front();
    current_cell.pop();
    if (current == end) {
      return BuildPath(steps, start, end);
    }
    for (auto neighbor : CheckNeighbors(current)) {
      if (!visited.count(neighbor)) {
        current_cell.push(neighbor);
        visited.insert(neighbor);
        steps.insert(std::make_pair(neighbor, current));
      }
    }
  }

  BuildPath(steps, start, end);
}

std::list<Coordinate> MazeSolution::GetPath() const noexcept {
  return best_path_;
}

void MazeSolution::SetMaze(std::shared_ptr<MazeInfo> mm) { maze_info_ = mm; }

std::list<Coordinate> MazeSolution::CheckNeighbors(const Coordinate cell) {
  std::list<Coordinate> neighbors;

  std::array<Coordinate, 4> directions = {cell.Up(), cell.Down(), cell.Left(),
                                          cell.Right()};

  if (directions[1].IsValid(maze_info_->height, maze_info_->width)) {
    if (!maze_info_->h_walls[cell.GetY()][cell.GetX()]) {
      neighbors.push_back(directions[1]);
    }
  }

  if (directions[3].IsValid(maze_info_->height, maze_info_->width)) {
    if (!maze_info_->v_walls[cell.GetY()][cell.GetX()]) {
      neighbors.push_back(directions[3]);
    }
  }

  if (directions[0].IsValid(maze_info_->height, maze_info_->width)) {
    if (!maze_info_->h_walls[directions[0].GetY()][directions[0].GetX()]) {
      neighbors.push_back(directions[0]);
    }
  }

  if (directions[2].IsValid(maze_info_->height, maze_info_->width)) {
    if (!maze_info_->v_walls[directions[2].GetY()][directions[2].GetX()]) {
      neighbors.push_back(directions[2]);
    }
  }

  return neighbors;
}

void MazeSolution::BuildPath(std::map<Coordinate, Coordinate>& steps,
                             const Coordinate& start, const Coordinate& end) {
  best_path_.clear();
  Coordinate current = end;

  while (current != start) {
    best_path_.push_back(current);
    if (steps.find(current) == steps.end()) {
      best_path_.clear();
      throw std::invalid_argument("Path doesn't find");
    }
    current = steps.find(current)->second;
  }

  best_path_.push_back(start);
  best_path_.reverse();
}

};  // namespace maze
