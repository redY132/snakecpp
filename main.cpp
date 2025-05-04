#include <chrono>
#include <cstdlib>
#include <deque>
#include <random>
#include <thread>
#include <utility>
#include <vector>
#include <curses.h>
#include "funcs.h"

std::vector<std::vector<char>> init_board(int size, int startX, int startY, std::deque<std::pair<int, int>>* body){
    std::vector<std::vector<char>> board;
    for(int i = 0; i < size; i++){
        std::vector<char> row;
        for(int j = 0; j < size; j++){
            row.push_back(' ');
        }
        board.push_back(row);
    }
    board[startY][startX] = 'X';
    body -> push_front(std::pair<int, int> {startX, startY});
    return board;
}

void print_screen(const std::vector<std::vector<char>>& board){
    clear();

    for(int y = 0; y < board.size(); y++){
        int row_len = (2 * board[y].size() + 3);
        char row[row_len];
        row[0] = 'O';
        for(int x = 1; x < (2 * board[y].size()); x+=2){
            row[x] = board[y][x/2];
            row[x + 1] = ' ';
        }
        row[row_len - 2] = 'O';
        row[row_len - 1] = '\0';
        printw("%s\n", row);
    }

    refresh();
};

void end_game(int score, int total){
    clear();
    if (score == total) {
        printw("You Win!\n");
    }
    else {
        printw("You Lose!\n");
    }
    printw("Score: %d/%d", score, total);
    refresh();
}

bool valid_position(std::pair<int, int>* cords_ptr, int size){
    if (cords_ptr -> first >= size || cords_ptr -> first < 0 ||
        cords_ptr -> second >= size || cords_ptr -> second < 0) 
    {
        return false;
    }
    else 
    {
        return true;
    }
}

//direction of 1 is x, direction of 0 is y
bool updateBoard(std::vector<std::vector<char>>& board, std::pair<int, int>* head_cords_ptr, 
                 bool moving_x, bool positive, int* score, std::deque<std::pair<int, int>>* snake_body){
    if(!valid_position(head_cords_ptr, board.size()) || *score == board.size() * board.size()){
        end_game(*score, board.size() * board.size());
        return false;
    }

    if (board[head_cords_ptr -> second][head_cords_ptr -> first] == 'X') {
        end_game(*score, board.size() * board.size());
        return false;
    }

    if(!(board[head_cords_ptr -> second][head_cords_ptr -> first] == '$'))
    {
        board[snake_body -> back().second][snake_body -> back().first] = ' ';
        snake_body->pop_back();
    }
    else{
        ++*score;
        if(*score == board.size() * board.size())
            end_game(*score, board.size() * board.size());
        createApples(board);
    };

    board[head_cords_ptr -> second][head_cords_ptr -> first] = 'X';

    snake_body -> push_front(*head_cords_ptr);

    return true;
}

void movePos(std::pair<int, int>* pos_pair_ptr, bool moving_x, bool positive){
    if(moving_x)
    {
        if (positive) {
            ++pos_pair_ptr -> first;
        }
        else {
            --pos_pair_ptr -> first;
        }
    }
    else {
        if (positive) {
            --pos_pair_ptr -> second;
        }
        else {
            ++pos_pair_ptr -> second;
        }
    }
}

void takeInput(bool* moving_x, bool* positive, bool* gameRunning){
    while (*gameRunning) {
        char input = getch();
        if(input == 'd')
        {
            *moving_x = true;
            *positive = true;
        }
        else if (input == 'a') {
            *moving_x = true;
            *positive = false;
        }
        else if (input == 'w') {
            *moving_x = false;
            *positive = true;
        }
        else if (input == 's') {
            *moving_x = false;
            *positive = false;
        }
    }
}

void createApples(std::vector<std::vector<char>>& board)
{
    while(true)
    {
        std::random_device rd;
        std::mt19937 gen (rd());
        std::uniform_int_distribution<> dist(0, board.size() - 1);
        int y = dist(gen);
        int x = dist(gen);
        if(board[y][x] != 'X'|| board[y][x] != 'O' || board[y][x] != '$')
        {
            board[y][x] = '$';
            break;
        }
    }
}

int main (int argc, char *argv[]) {
    initscr();
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);

    printw("Type Preferred Size\n");
    refresh();

    char buffer[2];
    getnstr(buffer, sizeof(buffer));

    int size = std::atoi(buffer);

    std::deque<std::pair<int, int>> snake_body;

    std::vector<std::vector<char>> board {init_board(size, 0, 0, &snake_body)};

    createApples(board);

    noecho();

    std::pair<int, int> head_cords {0, 0};
    std::pair<int, int> tail_cords {0, 0};
    int char_score {0};
    bool moving_x {true};
    bool positive {true};

    bool gameRunning {true};

    std::thread inputThread(takeInput, &moving_x, &positive, &gameRunning);


    while(gameRunning){
        print_screen(board);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        movePos(&head_cords, moving_x, positive);
        gameRunning = updateBoard(board, &head_cords, moving_x, positive, &char_score, &snake_body);
    }

    inputThread.detach();
    
    getch();
    endwin();

    return 0;
}
