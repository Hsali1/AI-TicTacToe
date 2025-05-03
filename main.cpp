#include <iostream>
#include <vector>
#include <random>

void printBoard(std::vector<std::vector<char>>);

int main(void){
    
    std::vector<std::vector<char>> board = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
    };

    int player_score, computer_score = 0;

    while(true) {
        std::cout << "Player: " << player_score << " Computer: " << computer_score << std::endl;
        printBoard(board);

        int current_player = 
        break;
    }
    
    return 0;
}

void printBoard(std::vector<std::vector<char>> board) {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            std::cout << '|' << board[i][j];
        }
        std::cout << "|\n";
    }
}