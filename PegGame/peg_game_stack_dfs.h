#ifndef STACK_DFS_H_
#define STACK_DFS_H_
#include "peg_game_state.h"

#include <vector>
#include <map>
#include <utility>

using std::vector;
using std::map;
using std::pair;

class PegGameStackDFS {
public:
  PegGameStackDFS(const PegGameState &, const PegGameState &, int);
  void Solve();
  void PrintPotentialMoves();
  void PrintPath(PegGameState *, const map<PegGameState *, PegGameState *> &);
private:
  PegGameState init_;
  PegGameState goal_;
  map<int, vector<pair<int, int>>> potential_jumps_;
  void GetMovesDiagonalRight(vector<int>);
  void GetMovesDiagonalLeft(vector<int>);
  void GetMovesRows(int);
};

#endif  //  STACK_DFS_H_