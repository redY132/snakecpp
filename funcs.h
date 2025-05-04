#ifndef FUNCS_GUARD
#define FUNCS_GUARD

#include <iostream>
#include <utility>
#include <vector>

std::vector<std::vector<char>> init_board(int, int, int);

void print_screen(const std::vector<std::vector<char>>&);

void end_game(int, int);

bool valid_position(std::pair<int,int>*, int);

void updateBoard(std::vector<std::vector<char>>&, std::pair<int,int>*, std::pair<int,int>*, bool, bool);

void movePos(std::pair<int, int>*, bool, bool);

void takeInput(bool*, bool*, bool*);

void createApples(std::vector<std::vector<char>>& board);

#endif
