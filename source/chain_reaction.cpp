#include <iostream>
#include "../include/board.h"
#include "../include/player.h"
#include "../include/rules.h"
#include "../include/algorithm.h"

using namespace std;

// for main data flow

int main(){

    Board board;
    Player red_player(RED);
    Player blue_player(BLUE);

    bool first_two_step = true;
    int round = 1;
    int index[2];

    while(1){

        //////////// Red Player operations ////////////
        algorithm_A(board, red_player, index);
        // "should" return a board index (i, j).
        board.place_orb(index[0], index[1], &red_player);
        // put your orb on the index that obtained from your algorithm.

        if(rules_violation(red_player)) {
           // cout << "(" << index[0] << "," << index[1] << ")" << endl;
            return 0;
        }
        // If a players' placement is illegal,
        // the program will terminate immediately and annouce the winner.

        board.print_current_board(index[0], index[1], round);
        round++;

        if(board.win_the_game(red_player) && !first_two_step){
            cout << "Red Player won the game !!!" << endl;
            return 0;
        }
        // If a players' last placement dominate the hole board,
        // the program will terminate immediately and annouce the winner.

        //////////// Blue Player operations ////////////
        
        algorithm_B(board, blue_player, index);
        board.place_orb(index[0], index[1], &blue_player);

        if(rules_violation(blue_player)) return 0;
        
        board.print_current_board(index[0], index[1], round);
        round++;

        if(board.win_the_game(blue_player) && !first_two_step){
            cout << "Blue Player won the game !!!" << endl;
            return 0;
        }

        first_two_step = false;
    }
    return 0;
} 