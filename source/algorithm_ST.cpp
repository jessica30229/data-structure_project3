#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "../include/algorithm.h"

using namespace std;

//compile command: $ g++ chain_reaction.cpp board.cpp rules.cpp player.cpp algorithm_ST.cpp algorithm_TA.cpp

/******************************************************
 * In your algorithm, you can just use the the funcitons
 * listed by TA to get the board information.(functions 
 * 1. ~ 4. are listed in next block)
 * 
 * The STL library functions is not allowed to use!!!!
*****************************************************/

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

#define max(a,b) (a)>(b)?(a):(b)
#define min(a,b) (a)<(b)?(a):(b)

#define MAX_INF     1000000000

// int dis_count[2] = {0};
// int maxeval = -1000000;
// int mineval = +1000000;
//int ans_idx;
// enum SPOT_STATE {
//     ME = 0,
//     OPPONENT = 1
// };
// int curplayer;
char my_color;
char opponet_color;
Player red_player(RED);
Player blue_player(BLUE);

//Player me;
struct Point{
    int row, col;
    //Point() : Point(0, 0, 0) {}
    Point() {}
    Point(int row, int col) : row(row), col(col) {}

    // Point operator+(const Point& rhs) const {
	// 	return Point(x + rhs.x, y + rhs.y);
	// }
	// Point operator-(const Point& rhs) const {
	// 	return Point(x - rhs.x, y - rhs.y);
	// }
};

// Point directions[8] = {
//     Point(-1, -1), Point(-1, 0), Point(-1, 1),
//     Point(0, -1), /*{0, 0},*/ Point(0, 1),
//     Point(1, -1), Point(1, 0), Point(1, 1)
// };

#if 1
int check_weight(Board* board){
    int weight = 0;
    for(int row=0;row<5;row++) {
        for(int col=0;col<6;col++) {
            char c = board->get_cell_color(row,col);
            int cap = board->get_cell_color(row,col);
            int num = board->get_orbs_num(row,col);

            if(c==RED) {
                switch(cap-num) {
                    case 1: weight += 10000; break;
                    case 2: weight += 1000; break;
                    default:
                        weight += 100; break;
                }
            } else if(c==BLUE) {
                switch(cap-num) {
                    case 1: weight -= 10000; break;
                    case 2: weight -= 1000; break;
                    default:
                        weight -= 100; break;
                }
            }
        }
    }
    return weight;
}

Point* get_valid_orbs(Board* board, char color, int* count){
    Point* valid_orbs = new Point[30];
    int idx = 0;
    for(int row = 0; row < 5; row++){
        for(int col = 0; col < 6; col++){
            if(board->get_cell_color(row, col) == color||board->get_cell_color(row,col) == 'w')
                valid_orbs[idx++] = Point(row,col);
        }
    }
    *count = idx;
    return valid_orbs;
}

void create_new_board(Board* newboard, Point p, char color, Board* board){
    // copy original
    *newboard = *board;

    Player player('w');
    if(color == 'r') player = red_player;
    else player = blue_player;
    newboard->place_orb(p.row, p.col, &player);
}

int minimax(Board* board, int depth, int alpha, int beta, bool isMaximizingPlayer, Point* ret_p){
    int v, new_v, count;

    if(depth==0) {
        ret_p = 0;
        return check_weight(board);
    }

    if(isMaximizingPlayer) {
        v = -MAX_INF;
        Point* valid_orbs = get_valid_orbs(board, my_color, &count);
        if(count==0) {
            cout << "max ERROR no valid orbs" << endl;
        }
        Point p, which_p;
        for(int i=0;i<count;i++) {
            Board nboard;
            // place new orb
            create_new_board(&nboard, valid_orbs[i], my_color, board);
            // find next best orb
            new_v = minimax(&nboard, depth-1, alpha, beta, false, &which_p);

            if(new_v>=v) {
                v = new_v;
                p = valid_orbs[i];
            }
            if(alpha>=v) {
                alpha = v;
            }
            if(alpha>=beta)
                break;
        }
        delete valid_orbs;
        *ret_p=p;
        return v;
    } else {
        v = +MAX_INF;
        Point* valid_orbs = get_valid_orbs(board, opponet_color, &count);
        if(count==0) {
            cout << "min ERROR no valid orbs" << endl;
        }
        Point p, which_p;
        for(int i=0;i<count;i++) {
            Board nboard;
            // place new orb
            create_new_board(&nboard, valid_orbs[i], opponet_color, board);
            // find next best orb
            new_v = minimax(&nboard, depth-1, alpha, beta, true, &which_p);
            if(new_v<=v) {
                v = new_v;
                p = valid_orbs[i];
            }
            if(beta<=v) {
                beta = v;
            }
            if(beta<=alpha)
                break;
        }
        delete valid_orbs;
        *ret_p=p;
        return v;
    }
}

void algorithm_A(Board board, Player player, int index[]){
    // int count;
    //////your algorithm design///////////
    if(player.get_color() == 'r') {my_color = 'r'; opponet_color = 'b';}
    else {my_color = 'b'; opponet_color = 'r';}

    Point p;
    
    minimax(&board, 4, -MAX_INF, +MAX_INF, true, &p);

    index[0] = p.row;
    index[1] = p.col;
}
#endif