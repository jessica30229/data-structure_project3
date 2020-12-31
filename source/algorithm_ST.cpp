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
******************************************source /Users/jessica/.gvm/scripts/gvm
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
#define min(a,b) a<b?a:b

int dis_count[2];
int maxeval = -1000000;
int mineval = +1000000;
enum SPOT_STATE {
    ME = 0,
    OPPONENT = 1
};
int curplayer = ME;
struct Point{
    int x, y;
    Point() : Point(0, 0) {}
    Point(int x, int y) : x(x), y(y) {}
    Point operator+(const Point& rhs) const {
		return Point(x + rhs.x, y + rhs.y);
	}
	Point operator-(const Point& rhs) const {
		return Point(x - rhs.x, y - rhs.y);
	}
};

Point directions[8] = {
    Point(-1, -1), Point(-1, 0), Point(-1, 1),
    Point(0, -1), /*{0, 0},*/ Point(0, 1),
    Point(1, -1), Point(1, 0), Point(1, 1)
};

// void ST_cell_reset(int i, int j){
//     cells[i][j].set_orbs_num(0);
//     cells[i][j].set_explode(false);
//     cells[i][j].set_color('w');
// }

// void change_cnt(Point p, Player player, Board board){
//     if(board.get_orbs_num(p.x, p.y)==board.get_capacity(p.x, p.y)){
//         for(Point dir: directions){
//             Point c = c + dir;
//             if(0 <= c.x && c.x < 5 && 0 <= c.y && c.y < 6){
//                 board.place_orb(c.x, c.y, &player);
//             }
//         }
//         board.
//     }      
// }

Board new_board(Point p, Player player, Board board){
    Board newboard;
    newboard = board;
    newboard.place_orb(p.x, p.y, &player);
    // change_cnt(p, player, newboard);
    return newboard;
}

int minimax(Point p, Board board, int depth, int alpha, int beta, bool isMaximizingPlayer){
    if(depth == 6)
        return dis_count[ME]-dis_count[OPPONENT];
    if(isMaximizingPlayer){
        curplayer = ME;
        Board newboard = new_board(p, curplayer, board);
        Point* child = get_valid_orbs(newboard, curplayer);
        for(int i = 0; i < sizeof(child); i++){
            int eval = minimax(child[i], newboard, depth+1, alpha, beta, false);
            maxeval = max(maxeval, eval);
            alpha = max(alpha, eval);
            if(beta <= alpha)
                break;
        }
        return maxeval;
    }else{
        curplayer = OPPONENT;
        Board newboard = new_board(p, curplayer, board);
        Point* child = get_valid_orbs(newboard, curplayer);
        for(int i = 0; i < sizeof(child); i++){
            int eval = minimax(child[i], newboard, depth+1, alpha, beta, true);
            mineval = min(mineval, eval);
            beta = min(beta, eval);
            if(beta <= alpha)
                break;
        }
        return mineval;
    }
    return 0;
}

Point* get_valid_orbs(Board board, Player player){
    Point validorbs[30];
    int idx = 0;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 6; j++){
            if(board.get_cell_color(i, j)!= player.get_color()) continue;
            else{
                validorbs[idx++] = Point(i, j);
            }
        }
    }
    return validorbs;
}

void algorithm_A(Board board, Player player, int index[]){
    //////your algorithm design///////////
    int ansval = -1000000;
    int ansidx = 0;
    Point* validorbs = get_valid_orbs(board, player);
    for(int i = 0; i < sizeof(validorbs); i++){
        maxeval = -1000000;
        mineval = +1000000;
        int nowval = minimax(validorbs[i], board, 0, -100000, 100000, true);
        ansval = max(ansval, nowval);
        if(ansval == nowval)
            ansidx = i;
    }
    Point ans = validorbs[ansidx]; 
    //if(board.get_cell_color(row, col) == color || board.get_cell_color(row, col) == 'w') break;
    index[0] = ans.x;
    index[1] = ans.y;
}