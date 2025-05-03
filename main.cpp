#include <iostream>
#include <vector>
#include <cctype>

#define PLAYER "\033[31mplayer\033[0m"
#define COMPUTER "\033[32mcomputer\033[0m"

void printBoard(const std::vector<std::vector<char>> &board);
char getChoice(const std::vector<std::vector<char>> &board);
void updateBoard(int, char, std::vector<std::vector<char>>&);
bool checkWinner(int, const std::vector<std::vector<char>> &);

int main(void){
    
    std::vector<std::vector<char>> board;

    int player_score, computer_score = 0;   // will capture the total wins of each player
    int turn;                               // used to check if there is a draw
    int current_player;                     // used to check current player
    bool game_over;                         // used to check if game is ongoing
    char choice;                            // used to capture player input

    while(true) {   // game loop
        board = {
            {'1', '2', '3'},
            {'4', '5', '6'},
            {'7', '8', '9'}
        };
        game_over = false;
        turn = 1;

        std::cout << "Player: \033[31m" << player_score << "\033[0m Computer: \033[32m";
        std::cout << computer_score << "\033[0m" << std::endl;

        // generate a random number between 0 and 1
        current_player = rand() % 2;

        std::cout << ((current_player == 0) ? PLAYER : COMPUTER) << " goes first!" << std::endl;

        while (!game_over){ // Match loop

            std::cout << "------Turn:" << turn << " ------" << std::endl;
            printBoard(board);
            std::cout << ((current_player == 0) ? PLAYER : COMPUTER) <<" choosing" << std::endl;

            choice = getChoice(board);
            updateBoard(current_player, choice, board);

            if (checkWinner(current_player, board)){
                game_over = true;
                std::cout << ((current_player == 0) ? "\033[31mplayer\033[0m" : "\033[32mcomputer\033[0m");
                std::cout <<" Has Won!" << std::endl;
                std::cout << "-----------------------" << std::endl;
                if (current_player == 0){
                    player_score++;
                } else {
                    computer_score++;
                }
                break;
            }
            current_player = (current_player == 0) ? 1 : 0;
            turn++;
            if (turn == 10){
                std::cout << "It's a draw, restarting" << std::endl;
                std::cout << "-----------------------" << std::endl;
                game_over = true;
            } else {
                system("clear");
                std::cout << "Player: \033[31m" << player_score << "\033[0m Computer: \033[32m";
                std::cout << computer_score << "\033[0m" << std::endl;
            }
        }
    }
    
    return 0;
}

void printBoard(const std::vector<std::vector<char>> &board) {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (board[i][j] == 'X'){
                std::cout << '|' << "  \033[31mX\033[0m  ";
                continue;
            }
            if (board[i][j] == 'O'){
                std::cout << '|' << "  \033[32mO\033[0m  ";
                continue;
            }
            std::cout << '|' << "  " << board[i][j] << "  ";
        }
        std::cout << "|\n-------------------\n";
    }
}

// Responsible for getting the choice and making sure it is a valid choice
char getChoice(const std::vector<std::vector<char>> &board) {
    char choice;
    bool is_valid = false;

    while (!is_valid){
        std::cout << "Enter number: ";
        std::cin >> choice;
        // check if choice is valid
        for (int i = 0; i < board.size(); i++) {
            if ((std::tolower(choice) == 'x') || ((std::tolower(choice) == 'o')))
                break;
            if (!is_valid){
                for (int j = 0; j < board[i].size(); j++) {
                    if (choice == board[i][j]) {
                        is_valid = true;
                        break;
                    }
                }
            } else {
                break;
            }
        }
        if (!is_valid){
            std::cout << "please enter a valid choice!!" << std::endl;
            continue;
        }
        break;
    }

    return choice;
}


void updateBoard(int current_player, char choice, std::vector<std::vector<char>> &board) {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (choice == board[i][j]) {
                board[i][j] = (current_player == 0) ? 'X' : 'O';
            }
        }
    }
}

bool checkWinner(int current_player, const std::vector<std::vector<char>> &board){

    char symbol = (current_player == 0) ? 'X' : 'O';

    // 8 winning conditions 3 rows, 3 columns, 2 diagnol
    // row 1
    if(symbol == board[0][0] && symbol == board[0][1] && symbol == board[0][2]){
        return true;
    }
    // row 2
    if(symbol == board[1][0] && symbol == board[1][1] && symbol == board[1][2]){
        return true;
    }
    // row 3
    if(symbol == board[2][0] && symbol == board[2][1] && symbol == board[2][2]){
        return true;
    }
    // column 1
    if(symbol == board[0][0] && symbol == board[1][0] && symbol == board[2][0]){
        return true;
    }
    // column 2
    if(symbol == board[0][1] && symbol == board[1][1] && symbol == board[2][1]){
        return true;
    }
    // column 3
    if(symbol == board[0][2] && symbol == board[1][2] && symbol == board[2][2]){
        return true;
    }
    // diag 1
    if(symbol == board[0][0] && symbol == board[1][1] && symbol == board[2][2]){
        return true;
    }
    // diag 2
    if(symbol == board[0][2] && symbol == board[1][1] && symbol == board[2][0]){
        return true;
    }
    return false;
}