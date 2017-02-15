#include "peg_game_state.h"
#include "peg_game_stack_dfs.h"

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <set>
#include <utility>
#include <chrono>
#include <stdlib.h>
#include <time.h>

using namespace std;
using namespace std::chrono;

//  jumpable neighbors
const int ROWS = 5;
const int BOARD_SIZE = ROWS * (ROWS + 1) / 2;

int main() {
  int input = 0;
  int n = 5;
  vector<bool> init_board(15, 1); init_board[0] = 0;
  vector<bool> goal_board(15, 0); goal_board[0] = 1;
  PegGameState *init = new PegGameState(init_board);
  PegGameState *goal = new PegGameState(goal_board);

  cout << "DIRECTIONS FOR ENTERING BOARD STATES\n";
  cout << "Enter the board as an array of 0's and 1's with spaces.\n";
  cout << "1's represent pegs, and 0's represent empty holes.\n";
  cout << "The pegs are entered starting at the first row with 1 hole continuing until the nth row with n holes.\n";
  cout << "Hence for a given board state with n rows it should have n(n+1)/2 holes.\n\n";
  cout << "Example input: 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1\n";
  cout << "Will result in:\n\n";
  cout << "    0\n";
  cout << "   1 1\n";
  cout << "  1 1 1\n";
  cout << " 1 1 1 1\n";
  cout << "1 1 1 1 1\n\n";


  while (input != 5) {
    cout << "\nMenu: \n";
    cout << "1) Enter solution specifications\n";
    cout << "2) Display initial board stae\n";
    cout << "3) Display goal board state\n";
    cout << "4) Solve\n";
    cout << "5) Exit\n\nSelection: ";
    cin >> input;

    switch (input) {
    case 1: {
      n = 0;
      cout << "Number of rows (n > 3): ";
      while (n <= 3) cin >> n;
      init_board.resize(n * (n + 1) / 2, 0);
      goal_board.resize(n * (n + 1) / 2, 0);
      cout << "Enter initial board state (" << n * (n + 1) / 2 << " entries): ";
      for (int i = 0; i < init_board.size(); ++i) {
        cin >> input;
        init_board[i] = input;
      }
      cout << "Enter goal board state: ";
      for (int i = 0; i < goal_board.size(); ++i) {
        cin >> input;
        goal_board[i] = input;
      }
      delete init;
      delete goal;
      init = new PegGameState(init_board, n);
      goal = new PegGameState(goal_board, n);
      input = 1;
      break;
    }
    case 2: {
      init->Print();
      break;
    }
    case 3: {
      goal->Print();
      break;
    }
    case 4: {
      high_resolution_clock::time_point t1 = high_resolution_clock::now();
      PegGameStackDFS solver(*init, *goal, n);
      solver.Solve();
      high_resolution_clock::time_point t2 = high_resolution_clock::now();
      auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
      cout << "Execution time: " << duration / 1000.0 << " seconds" << endl;
      break;
    }
    }
  }
  return 0;
}