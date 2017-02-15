#ifndef PEG_GAME_STATE_H_
#define PEG_GAME_STATE_H_

#include <vector>

using std::vector;

class PegGameState {
public:
  PegGameState() {}
  PegGameState(const vector<bool> &);
  PegGameState(const vector<bool> &, int);
  PegGameState(int, int);
  void Jump(int, int, int);
  void Print() const;
  PegGameState *get_state() const { return (new PegGameState(*this)); }
  int get_rows() const { return this->rows_; }
  int get_board_size() const { return this->board_.size(); }
  bool get_peg_val(int i) const { return this->board_[i]; }
  const vector<bool> &get_board() const { return this->board_; }
  void set_board(const vector<bool> &board) { this->board_ = board; }
  void set_rows(int rows) { this->rows_ = rows; }
  bool operator<(const PegGameState &) const;
  bool operator==(const PegGameState &) const;
private:
  vector<bool> board_;
  int rows_;
};

#endif  //  PEG_GAME_STATE_H_