#include "peg_game_state.h";

#include <vector>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

PegGameState::PegGameState(const vector<bool> &board) {
  this->rows_ = (-1 + sqrt(1 + 4 * 2 * board.size())) / 2;
  for (int i = 0; i < board.size(); ++i) {
    this->board_.push_back(board[i]);
  }
}

PegGameState::PegGameState(const vector<bool> &board, int rows) {
  this->rows_ = rows;
  for (int i = 0; i < board.size(); ++i)
    this->board_.push_back(board[i]);
}

PegGameState::PegGameState(int start, int rows) {
  this->rows_ = rows;
  for (int i = 0; i < rows * (rows + 1) / 2; ++i) {
    if (i == start) {
      this->board_.push_back(0);
    } else {
      this->board_.push_back(1);
    }
  }
  this->Print();
}

void PegGameState::Jump(int origin, int middle, int destination) {
  this->board_[origin] = false;
  this->board_[middle] = false;
  this->board_[destination] = true;
}

bool PegGameState::operator<(const PegGameState &second) const {
  for (int i = 0; i < this->get_board_size(); ++i) {
    if (this->get_peg_val(i) != second.get_peg_val(i)) {
      if (this->get_peg_val(i) < second.get_peg_val(i)) return true;
      else return false;
    }
  }
  return false;
}

bool PegGameState::operator==(const PegGameState &comp) const {
  for (int i = 0; i < this->board_.size(); ++i) {
    if (this->board_[i] != comp.board_[i]) return false;
  }
  return true;
}

void PegGameState::Print() const {
  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < this->rows_ - (i + 1); ++j) cout << " ";
    for (int j = i * (i + 1) / 2; j < (i + 1) * (i + 2) / 2; ++j) {
      cout << this->board_[j] << " ";
    } cout << endl;
  } cout << endl;
}