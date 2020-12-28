#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "../include/algorithm.h"

using namespace std;

//compile command: $g++ chain_reaction.cpp board.cpp rules.cpp player.cpp algorithm_ST.cpp algorithm_TA.cpp

/******************************************************
 * In your algorithm, you can just use the the funcitons
 * listed by TA to get the board information.(functions 
 * 1. ~ 4. are listed in next block)
 * 
 * The STL library functions is not allowed to use!!!!
******************************************************/

/*************************************************************************
 * 1. int board.get_orbs_num(int row_index, int col_index)
 * 2. int board.get_capacity(int row_index, int col_index)
 * 3. char board.get_cell_color(int row_index, int col_index)
 * 4. void board.print_current_board(int row_index, int col_index, int round)
 * 
 * 1. The function that return the number of orbs in cell(row, col)
 * 2. The function that return the orb capacity of the cell(row, col)
 * 3. The function that return the color fo the cell(row, col)
 * 4. The function that print out the current board statement
*************************************************************************/

int dis_count[2];
struct Point{
    int x, y;
    int value;
    Point() : Point(0, 0, 0) {}
    Point(int x, int y, int value) : x(x), y(y), value(value){}
};

Board new_board(Point p, Player player, Board board){
    Board newboard;
    newboard = board;
    newboard.place_orb(p.x, p.y, &player);
}

int64_t minimax(Board board, int depth, bool isMaximizingPlayer){
// if current board state is a terminal state :
//     return value of the board
    if(depth == 6)
        return dis_count[]-dis_count[];
    if(isMaximizingPlayer){
        
    }
// if isMaximizingPlayer :
//     bestVal = -INFINITY 
//     for each move in board
//             value = minimax(board, depth+1, false)
//             bestVal = max( bestVal, value) 
//         return bestVal

//     else :
//         bestVal = +INFINITY 
//         for each move in board :
//             value = minimax(board, depth+1, true)
//             bestVal = min( bestVal, value) 
//         return bestVal;
}

Point* get_valid_orbs(Board board, Player player){
    Point validorbs[30];
    int idx = 0;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 6; j++){
            if(board.get_cell_color(i, j)!= player.get_color()) continue;
            else{
                validorbs[idx++] = Point(i, j, 0);
            }
        }
    }
}

void algorithm_A(Board board, Player player, int index[]){

    //////your algorithm design///////////
    Point ans;
    Point* validorbs = get_valid_orbs(board, player);
    for(int i = 0; i < sizeof(validorbs); i++){

    }
    //minmax(board, 0, true);
    //if(board.get_cell_color(row, col) == color || board.get_cell_color(row, col) == 'w') break;
    index[0] = ans.x;
    index[1] = ans.y;
}