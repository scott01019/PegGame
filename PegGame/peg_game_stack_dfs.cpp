#include "peg_game_stack_dfs.h"
#include "peg_game_state.h"

#include <vector>
#include <map>
#include <utility>
#include <iostream>
#include <stack>
#include <set>
#include <string>

using std::vector;
using std::pair;
using std::map;
using std::stack;
using std::set;
using std::string;
using std::cout;
using std::endl;

PegGameStackDFS::PegGameStackDFS(const PegGameState &init, const PegGameState &goal, int rows) : init_(init), goal_(goal) {
  vector<int> diagonal_moves_right;
  for (int i = rows; i > 0; --i) {
    diagonal_moves_right.push_back(i * (i + 1) / 2);
  }

  vector<int> diagonal_moves_left;
  for (int i = rows - 1; i > -1; --i) {
    diagonal_moves_left.push_back(1 + i * (i + 1) / 2);
  }

  GetMovesRows(rows);
  GetMovesDiagonalRight(diagonal_moves_right);
  GetMovesDiagonalLeft(diagonal_moves_left);
}

void PegGameStackDFS::Solve() {
  stack<PegGameState *> stack;
  set<PegGameState> visited;
  map<PegGameState *, PegGameState *> parents;
  bool solved = false;
  stack.push(&this->init_);
  parents.insert(pair<PegGameState*, PegGameState*>(&this->init_, nullptr));
  while (!stack.empty()) {
    PegGameState *current = stack.top();
    stack.pop();
    if (*current == this->goal_) {
      solved = true;
      cout << "\nSolution: \n\n";
      this->PrintPath(current, parents);
      break;
    }
    if (visited.find(*current) == visited.end()) {
      visited.insert(*current);
      for (int i = 0; i < current->get_board_size(); ++i) {
        if (current->get_peg_val(i) == 1) {
          vector<pair<int, int>> potential_jumps_for_peg = this->potential_jumps_.at(i);
          for (int j = 0; j < potential_jumps_for_peg.size(); ++j) {
            int neighbor_peg = potential_jumps_for_peg[j].first;
            int dest_peg = potential_jumps_for_peg[j].second;
            if (current->get_peg_val(neighbor_peg) == 1 && current->get_peg_val(dest_peg) == 0) {
              PegGameState *neighbor_state = new PegGameState(current->get_board(), current->get_rows());
              neighbor_state->Jump(i, neighbor_peg, dest_peg);
              if (visited.find(*neighbor_state) == visited.end()) {
                parents.insert(pair<PegGameState*, PegGameState*>(neighbor_state, current));
                stack.push(neighbor_state);
              }
            }
          }
        }
      }
    }
  }
  if (!solved) {
    cout << "\nNo solution found!\n";
  }
}

void PegGameStackDFS::PrintPath(PegGameState *current, const map<PegGameState *, PegGameState *> &parents) {
  if (current == nullptr) {
    return;
  }
  PegGameState *parent = parents.at(current);
  this->PrintPath(parent, parents);
  current->Print();
}


void PegGameStackDFS::PrintPotentialMoves() {
  std::map<int, vector<pair<int, int>>>::iterator it = potential_jumps_.begin();
  for (it; it != potential_jumps_.end(); ++it) {
    cout << it->first << endl;
    for (int i = 0; i < it->second.size(); i++) {
      cout << "(" << it->second[i].first << ", " << it->second[i].second << ") ";
    }
    cout << endl << endl;
  }
}

void PegGameStackDFS::GetMovesDiagonalRight(vector<int> vec) {
  while (vec.size() > 2) {
    for (int i = 0; i < vec.size() - 2; ++i) {
      if (i + 2 < vec.size()) {
        int first = vec[i] - 1;
        int mid = vec[i + 1] - 1;
        int second = vec[i + 2] - 1;

        if (this->potential_jumps_.find(first) != this->potential_jumps_.end()) {
          this->potential_jumps_.at(first).push_back(pair<int, int>(mid, second));
        } else {
          this->potential_jumps_.insert(pair<int, vector<pair<int, int>>>(first, vector<pair<int, int>>({ pair<int, int>(mid, second) })));
        }

        if (this->potential_jumps_.find(second) != this->potential_jumps_.end()) {
          this->potential_jumps_.at(second).push_back(pair<int, int>(mid, first));
        } else {
          this->potential_jumps_.insert(pair<int, vector<pair<int, int>>>(second, vector<pair<int, int>>({ pair<int, int>(mid, first) })));
        }
      }
    }

    vec.pop_back();
    for (int i = 0; i < vec.size(); ++i) vec[i] -= 1;
  }
}

void PegGameStackDFS::GetMovesDiagonalLeft(vector<int> vec) {
  while (vec.size() > 2) {
    for (int i = 0; i < vec.size(); ++i) {
      if (i + 2 < vec.size()) {
        int first = vec[i] - 1;
        int mid = vec[i + 1] - 1;
        int second = vec[i + 2] - 1;

        if (this->potential_jumps_.find(first) != this->potential_jumps_.end()) {
          this->potential_jumps_.at(first).push_back(pair<int, int>(mid, second));
        } else {
          this->potential_jumps_.insert(pair<int, vector<pair<int, int>>>(first, vector<pair<int, int>>({ pair<int, int>(mid, second) })));
        }

        if (this->potential_jumps_.find(second) != this->potential_jumps_.end()) {
          this->potential_jumps_.at(second).push_back(pair<int, int>(mid, first));
        } else {
          this->potential_jumps_.insert(pair<int, vector<pair<int, int>>>(second, vector<pair<int, int>>({ pair<int, int>(mid, first) })));
        }
      }
    }

    vec.pop_back();
    for (int i = 0; i < vec.size(); ++i) vec[i] += 1;
  }
}

void PegGameStackDFS::GetMovesRows(int rows) {
  for (int i = 3; i < rows + 1; ++i) {
    vector<int> row;
    for (int j = 0; j < i; ++j) row.push_back(i * (i + 1) / 2 - j);
    for (int j = 0; j < row.size(); j++) {
      if (j + 2 < row.size()) {
        int first = row[j] - 1;
        int mid = row[j + 1] - 1;
        int second = row[j + 2] - 1;

        if (this->potential_jumps_.find(first) != this->potential_jumps_.end()) {
          this->potential_jumps_.at(first).push_back(pair<int, int>(mid, second));
        } else {
          this->potential_jumps_.insert(pair<int, vector<pair<int, int>>>(first, vector<pair<int, int>>({ pair<int, int>(mid, second) })));
        }

        if (this->potential_jumps_.find(second) != this->potential_jumps_.end()) {
          this->potential_jumps_.at(second).push_back(pair<int, int>(mid, first));
        } else {
          this->potential_jumps_.insert(pair<int, vector<pair<int, int>>>(second, vector<pair<int, int>>({ pair<int, int>(mid, first) })));
        }
      }
    }
  }
}