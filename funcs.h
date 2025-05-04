#ifndef FUNCS_GUARD
#define FUNCS_GUARD

#include <deque>
#include <vector>
#include <utility>

std::vector<std::vector<char>> init_board(int, int, int, std::deque<std::pair<int, int>>*);

void print_screen(const std::vector<std::vector<char>>&);

void end_game(int, int);

bool valid_position(std::pair<int,int>*, int);

void updateBoard(std::vector<std::vector<char>>&, bool, bool, int*, std::deque<std::pair<int, int>*>);

void movePos(std::pair<int, int>*, bool, bool);

void takeInput(bool*, bool*, bool*);

void createApples(std::vector<std::vector<char>>& board);

#endif
