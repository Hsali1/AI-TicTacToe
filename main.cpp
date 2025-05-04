#include <iostream>
#include <vector>
#include <cctype>
#include <limits>

#define PLAYER "\033[31mplayer\033[0m"
#define COMPUTER "\033[32mcomputer\033[0m"

void printBoard(const std::vector<std::vector<char>> &);
char getChoice(int, std::vector<std::vector<char>> &);
void updateBoard(char, char, std::vector<std::vector<char>>&);
char checkWinner(const std::vector<std::vector<char>> &);
char computerChoice(const std::vector<std::vector<char>> &);
char computerChoice2(std::vector<std::vector<char>> &, int);
int minimax(std::vector<std::vector<char>> &, int, bool);

int main(void){
    
    std::vector<std::vector<char>> board;

    int player_score, computer_score = 0;   // will capture the total wins of each player
    int turn;                               // used to check if there is a draw
    int current_player;                     // used to check current player
    char player_symbol;
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
        player_symbol = (current_player == 0) ? 'X' : 'O';

        std::cout << ((current_player == 0) ? PLAYER : COMPUTER) << " goes first!" << std::endl;

        std::cout << "------Turn:" << turn << " ------" << std::endl;
        printBoard(board);

        while (!game_over){ // Match loop

            std::cout << ((current_player == 0) ? PLAYER : COMPUTER) <<" choosing" << std::endl;

            choice = getChoice(current_player, board);
            updateBoard(player_symbol, choice, board);

            std::cout << "------Turn:" << turn << " ------" << std::endl;
            printBoard(board);

            char winner = checkWinner(board);
            if (winner == 'X' || winner == 'O'){
                game_over = true;
                std::cout << ((current_player == 0) ? "\033[31mplayer\033[0m" : "\033[32mcomputer\033[0m");
                std::cout <<" Has Won!" << std::endl;
                std::cout << "-----------------------" << std::endl;
                if (current_player == 0){
                    player_score++;
                } else {
                    computer_score++;
                }
            } else if (winner == 'D') {
                // printBoard(board);
                std::cout << "It's a draw, restarting" << std::endl;
                std::cout << "-----------------------" << std::endl;
                game_over = true;
            } else {
                current_player = (current_player == 0) ? 1 : 0;
                player_symbol = (current_player == 0) ? 'X' : 'O';
                turn++;
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
char getChoice(int player, std::vector<std::vector<char>> &board) {
    char choice;
    bool is_valid = false;

    while (!is_valid){
        if (player == 1) {
            choice = computerChoice2(board, player);
        } else {
            std::cout << "Enter number: ";
            std::cin >> choice;
        }
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

char computerChoice2(std::vector<std::vector<char>> &board, int player) {
    int best_score = std::numeric_limits<int>::min();
    char best_move, current_val;
    int score;
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board.size(); j++) {
            if ((board[i][j] != 'X') && board[i][j] != 'O'){
                current_val = board[i][j];
                board[i][j] = 'O';
                int score = minimax(board, 0, false);
                board[i][j] = current_val;
                if (score > best_score){
                    best_score = score;
                    best_move = current_val;
                }
            }
        }
    }
    char choice = best_move;
    return choice;
}

int minimax(std::vector<std::vector<char>> &board, int depth, bool isMaximising){
    char result = checkWinner(board);
    if (result == 'O') return 10 - depth;
    if (result == 'X') return depth - 10;
    if (result == 'D') return 0;  
    
    if (isMaximising) {
        int best_score = std::numeric_limits<int>::min();
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[i].size(); j++) {
                if (board[i][j] != 'X' && board[i][j] != 'O') {
                    char temp = board[i][j];
                    board[i][j] = 'O';
                    best_score = std::max(best_score, minimax(board, depth + 1, false));
                    board[i][j] = temp;
                }
            }
        }
        return best_score;
    } else {
        int worst_score = std::numeric_limits<int>::max();
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[i].size(); j++) {
                if (board[i][j] != 'X' && board[i][j] != 'O') {
                    char temp = board[i][j];
                    board[i][j] = 'X';
                    worst_score = std::min(worst_score, minimax(board, depth + 1, true));
                    board[i][j] = temp;
                }
            }
        }
        return worst_score;
    }
}

void updateBoard(char symbol, char choice, std::vector<std::vector<char>> &board) {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (choice == board[i][j]) {
                board[i][j] = symbol;
            }
        }
    }
}

char checkWinner(const std::vector<std::vector<char>> &board){

    // 8 winning conditions 3 rows, 3 columns, 2 diagnol
    // check for X
    // row 1
    if('X' == board[0][0] && 'X' == board[0][1] && 'X' == board[0][2]){
        return 'X';
    }
    // row 2
    if('X' == board[1][0] && 'X' == board[1][1] && 'X' == board[1][2]){
        return 'X';
    }
    // row 3
    if('X' == board[2][0] && 'X' == board[2][1] && 'X' == board[2][2]){
        return 'X';
    }
    // column 1
    if('X' == board[0][0] && 'X' == board[1][0] && 'X' == board[2][0]){
        return 'X';
    }
    // column 2
    if('X' == board[0][1] && 'X' == board[1][1] && 'X' == board[2][1]){
        return 'X';
    }
    // column 3
    if('X' == board[0][2] && 'X' == board[1][2] && 'X' == board[2][2]){
        return 'X';
    }
    // diag 1
    if('X' == board[0][0] && 'X' == board[1][1] && 'X' == board[2][2]){
        return 'X';
    }
    // diag 2
    if('X' == board[0][2] && 'X' == board[1][1] && 'X' == board[2][0]){
        return 'X';
    }
    // check for O
    // row 1
    if('O' == board[0][0] && 'O' == board[0][1] && 'O' == board[0][2]){
        return 'O';
    }
    // row 2
    if('O' == board[1][0] && 'O' == board[1][1] && 'O' == board[1][2]){
        return 'O';
    }
    // row 3
    if('O' == board[2][0] && 'O' == board[2][1] && 'O' == board[2][2]){
        return 'O';
    }
    // column 1
    if('O' == board[0][0] && 'O' == board[1][0] && 'O' == board[2][0]){
        return 'O';
    }
    // column 2
    if('O' == board[0][1] && 'O' == board[1][1] && 'O' == board[2][1]){
        return 'O';
    }
    // column 3
    if('O' == board[0][2] && 'O' == board[1][2] && 'O' == board[2][2]){
        return 'O';
    }
    // diag 1
    if('O' == board[0][0] && 'O' == board[1][1] && 'O' == board[2][2]){
        return 'O';
    }
    // diag 2
    if('O' == board[0][2] && 'O' == board[1][1] && 'O' == board[2][0]){
        return 'O';
    }

    // check for draw:
    std::vector<char> available_choices;
    for (int i = 0; i < board.size(); i ++) {
        for (int j = 0; j < board[i].size(); j++) {
            if ((board[i][j] != 'X') && board[i][j] != 'O'){
                auto pos = available_choices.begin();
                available_choices.insert(pos, board[i][j]);
            }
        }
    }
    if (available_choices.size() == 0) {
        return 'D';
    }
    
    return ' ';
}