GXX = g++
GXXFLAGS = -Wall -g -std=c++11

PegGame: main.o peg_game_stack_dfs.o peg_game_state.o
	$(GXX) $(GXXFLAGS) -o PegGame main.o peg_game_stack_dfs.o peg_game_state.o

main.o: main.cpp peg_game_stack_dfs.h peg_game_state.h
	$(GXX) $(GXXFLAGS) -c main.cpp

peg_game_stack_dfs.o: peg_game_stack_dfs.h peg_game_state.h
	$(GXX) $(GXXFLAGS) -c peg_game_stack_dfs.cpp

peg_game_state.o: peg_game_state.h
	$(GXX) $(GXXFLAGS) -c peg_game_state.cpp
