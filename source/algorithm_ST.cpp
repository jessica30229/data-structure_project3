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

#define max(a,b) a>b?a:b

int dis_count[2];
int maxeavl = -1000000;
int mineval = +1000000;
enum SPOT_STATE {
    ME = 0,
    OPPONENT = 1
};
int curplayer = ME;
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
    return newboard;
}

int minimax(Point p, Board board, int depth, int alphha, int beta, bool isMaximizingPlayer){
// if current board state is a terminal state :
//     return value of the board
    if(depth == 6)
        // return dis_count[]-dis_count[];
    if(isMaximizingPlayer){
        curplayer = ME;

    }else{
        curplayer = OPPONENT;
    }
    return 0;
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
    int ansval = -1000000;
    int ansidx = 0;
    Point* validorbs = get_valid_orbs(board, player);
    for(int i = 0; i < sizeof(validorbs); i++){
        maxeavl = -1000000;
        mineval = +1000000;
        int nowval = minimax(validorbs[i] ,board, 0, -100000, 100000, false);
        ansval = max(ansval, nowval);
        if(ansval == nowval)
            ansidx = i;
    }
    Point ans = validorbs[ansidx]; 
    //if(board.get_cell_color(row, col) == color || board.get_cell_color(row, col) == 'w') break;
    index[0] = ans.x;
    index[1] = ans.y;
}