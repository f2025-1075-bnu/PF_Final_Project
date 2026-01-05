#include <iostream>
#include <fstream>
using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define BLUE    "\033[34m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"

char board[3][3] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'}
};

char currentPlayer = 'X';

void displayBoard() {
    cout << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << " ";
            if (board[i][j] == 'X')
                cout << RED << board[i][j] << RESET;
            else if (board[i][j] == 'O')
                cout << BLUE << board[i][j] << RESET;
            else
                cout << board[i][j];

            cout << " ";
            if (j < 2) cout << YELLOW << "|" << RESET;
        }
        cout << endl;
        if (i < 2) cout << YELLOW << "---|---|---" << RESET << endl;
    }
    cout << endl;
}

bool placeMark(int choice) {
    int row = (choice - 1) / 3;
    int col = (choice - 1) % 3;

    if (board[row][col] != 'X' && board[row][col] != 'O') {
        board[row][col] = currentPlayer;
        return true;
    }
    return false;
}

bool checkWin() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == currentPlayer &&
            board[i][1] == currentPlayer &&
            board[i][2] == currentPlayer)
            return true;

        if (board[0][i] == currentPlayer &&
            board[1][i] == currentPlayer &&
            board[2][i] == currentPlayer)
            return true;
    }

    if (board[0][0] == currentPlayer &&
        board[1][1] == currentPlayer &&
        board[2][2] == currentPlayer)
        return true;

    if (board[0][2] == currentPlayer &&
        board[1][1] == currentPlayer &&
        board[2][0] == currentPlayer)
        return true;

    return false;
}

bool checkDraw() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return false;
    return true;
}

void saveResult(string result) {
    ofstream file("tictactoe_results.txt", ios::app);
    if (file.is_open()) {
        file << result << endl;
        file.close();
    }
}

int main() {
    int choice;
    bool gameOver = false;

    cout << GREEN << "TIC TAC TOE GAME (C++)" << RESET << endl;
    cout << RED << "Player 1 = X" << RESET << endl;
    cout << BLUE << "Player 2 = O" << RESET << endl;

    while (!gameOver) {
        displayBoard();
        cout << "Player "
             << (currentPlayer == 'X' ? RED : BLUE)
             << currentPlayer << RESET
             << ", enter your move (1-9): ";
        cin >> choice;

        if (choice < 1 || choice > 9 || !placeMark(choice)) {
            cout << "Invalid move. Try again." << endl;
            continue;
        }

        if (checkWin()) {
            displayBoard();
            cout << GREEN << "Player " << currentPlayer << " wins!" << RESET << endl;
            saveResult("Winner: Player " + string(1, currentPlayer));
            gameOver = true;
        }
        else if (checkDraw()) {
            displayBoard();
            cout << GREEN << "It's a draw!" << RESET << endl;
            saveResult("Result: Draw");
            gameOver = true;
        }
        else {
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }

    return 0;
}
