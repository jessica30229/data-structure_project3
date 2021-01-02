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

#define max(a,b) a>b?a:b
#define min(a,b) a<b?a:b

int dis_count[2] = {0};
int maxeval = -1000000;
int mineval = +1000000;
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
    int x, y, value;
    //Point() : Point(0, 0, 0) {}
    Point() {}
    Point(int x, int y) : x(x), y(y) {}
    Point(int x, int y, int value) : x(x), y(y), value(value){}
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

static int hit_count=0;

Point check_weight(Point p, char color, Board* board){
    hit_count++;

    int opponent_num = 0;
    int my_num = 0;
    int own_num = /*board->get_capacity(p.x, p.y) -*/ board->get_orbs_num(p.x, p.y)/board->get_capacity(p.x, p.y);
    //int spark = 0;
    for(int i = 0; i < 8; i++){
        Point n = p + directions[i];
        if(0 <= n.x && n.x < 5 && 0 <= n.y && n.y < 6){
            if(board->get_cell_color(n.x, n.y) == color)
                my_num = my_num + board->get_orbs_num(n.x, n.y)/board->get_capacity(n.x, n.y); //small is better
                // if(board->get_orbs_num(n.x, n.y)+1 == board->get_capacity(n.x, n.y))
                //     spark++;
            else{
                opponent_num = opponent_num + /* -*/ board->get_orbs_num(n.x, n.y);
            }
        }
    }
    return Point(p.x, p.y, (opponent_num+my_num)+own_num)/*(-opponent_num)-own_num-my_num)*/;
}

Point* get_valid_orbs(Board* board, char color, int* count){
    Point* valid_orbs = new Point[30];
    int idx = 0;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 6; j++){
            if(board->get_cell_color(i, j) == color||board->get_cell_color(i, j) == 'w')
                valid_orbs[idx++] = check_weight(Point(i, j), color, board);
        }
    }
    // cout << idx << "\n";
    *count = idx;
    return valid_orbs;
}

Board new_board(Point p, char color, Board* board){
    Board newboard;
    newboard = *board;
    Player player('w');
    if(color == 'r') player = red_player;
    else player = blue_player;
    newboard.place_orb(p.x, p.y, &player);
    // change_cnt(p, player, newboard);
    return newboard;
}

int minimax(Point p, Board* board, int depth, int alpha, int beta, bool isMaximizingPlayer){
    int count;
    if(depth == 4)//||board.win_the_game(me))
        return p.value;
    if(isMaximizingPlayer){
        Board newboard = new_board(p, opponet_color, board);
        Point* child = get_valid_orbs(&newboard, my_color, &count);
        for(int i = 0; i < count; i++){
            int eval = minimax(child[i], &newboard, depth+1, alpha, beta, false);
            maxeval = max(maxeval, eval);
            alpha = max(alpha, eval);
            if(beta <= alpha)
                break;
        }
        return maxeval;
    }else{
        Board newboard = new_board(p, my_color, board);
        Point* child = get_valid_orbs(&newboard, opponet_color, &count);
        for(int i = 0; i < count; i++){
            int eval = minimax(child[i], &newboard, depth+1, alpha, beta, true);
            mineval = min(mineval, eval);
            beta = min(beta, eval);
            if(beta <= alpha)
                break;
        }
        return mineval;
    }
    return 0;
}

void algorithm_A(Board board, Player player, int index[]){
    int count;
    //////your algorithm design///////////
    if(player.get_color() == 'r') {my_color = 'r'; opponet_color = 'b';}
    else {my_color = 'b'; opponet_color = 'r';}
    int ansval = -1000000;
    int ansidx = 0;
    Point* validorbs = get_valid_orbs(&board, my_color, &count);
    for(int i = 0; i < count; i++){
        maxeval = -1000000;
        mineval = +1000000;
        int nowval = minimax(validorbs[i], &board, 0, -100000, 100000, false);
        ansval = max(ansval, nowval);
        if(ansval == nowval)
            ansidx = i;
    }
    Point ans = validorbs[ansidx]; 
    //if(board.get_cell_color(row, col) == color || board.get_cell_color(row, col) == 'w') break;
    index[0] = ans.x;
    index[1] = ans.y;
}

void algorithm_ST_final()
{
    cout << hit_count << endl;    
}