#include <iostream>
#include <limits>
#include <vector>

using namespace std;

const char HUMAN = 'X';
const char AI = 'O';
const char EMPTY = ' ';

void printBoard(const vector<char>& board) {
    cout << "\n";
    for (int i = 0; i < 9; i++) {
        cout << " " << board[i] << " ";
        if (i % 3 != 2) cout << "|";
        if (i % 3 == 2 && i != 8) cout << "\n---+---+---\n";
    }
    cout << "\n\n";
}

void printPositions() {
    cout << "Choose positions like this:\n\n";
    cout << " 1 | 2 | 3 \n";
    cout << "---+---+---\n";
    cout << " 4 | 5 | 6 \n";
    cout << "---+---+---\n";
    cout << " 7 | 8 | 9 \n\n";
}

char checkWinner(const vector<char>& board) {
    int wins[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
        {0, 4, 8}, {2, 4, 6}
    };

    for (auto& line : wins) {
        char a = board[line[0]];
        char b = board[line[1]];
        char c = board[line[2]];

        if (a != EMPTY && a == b && b == c) {
            return a;
        }
    }

    for (char cell : board) {
        if (cell == EMPTY) return EMPTY;
    }

    return 'D'; // Draw
}

int minimax(vector<char>& board, bool isAiTurn) {
    char result = checkWinner(board);

    if (result == AI) return 10;
    if (result == HUMAN) return -10;
    if (result == 'D') return 0;

    if (isAiTurn) {
        int bestScore = -1000;

        for (int i = 0; i < 9; i++) {
            if (board[i] == EMPTY) {
                board[i] = AI;
                int score = minimax(board, false);
                board[i] = EMPTY;
                bestScore = max(bestScore, score);
            }
        }

        return bestScore;
    }

    int bestScore = 1000;

    for (int i = 0; i < 9; i++) {
        if (board[i] == EMPTY) {
            board[i] = HUMAN;
            int score = minimax(board, true);
            board[i] = EMPTY;
            bestScore = min(bestScore, score);
        }
    }

    return bestScore;
}

int getBestMove(vector<char>& board) {
    int bestScore = -1000;
    int bestMove = -1;

    for (int i = 0; i < 9; i++) {
        if (board[i] == EMPTY) {
            board[i] = AI;
            int score = minimax(board, false);
            board[i] = EMPTY;

            if (score > bestScore) {
                bestScore = score;
                bestMove = i;
            }
        }
    }

    return bestMove;
}

int getHumanMove(const vector<char>& board) {
    int move;

    while (true) {
        cout << "Enter your move (1-9): ";
        cin >> move;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a number.\n";
            continue;
        }

        if (move < 1 || move > 9) {
            cout << "Position must be between 1 and 9.\n";
            continue;
        }

        if (board[move - 1] != EMPTY) {
            cout << "That position is already taken.\n";
            continue;
        }

        return move - 1;
    }
}

int main() {
    vector<char> board(9, EMPTY);

    cout << "Tic-Tac-Toe With AI\n";
    cout << "You are X. Computer is O.\n\n";
    printPositions();

    while (true) {
        printBoard(board);

        int humanMove = getHumanMove(board);
        board[humanMove] = HUMAN;

        char result = checkWinner(board);
        if (result != EMPTY) {
            printBoard(board);
            if (result == HUMAN) cout << "You win!\n";
            else if (result == AI) cout << "Computer wins!\n";
            else cout << "It's a draw!\n";
            break;
        }

        int aiMove = getBestMove(board);
        board[aiMove] = AI;
        cout << "Computer chose position " << aiMove + 1 << ".\n";

        result = checkWinner(board);
        if (result != EMPTY) {
            printBoard(board);
            if (result == HUMAN) cout << "You win!\n";
            else if (result == AI) cout << "Computer wins!\n";
            else cout << "It's a draw!\n";
            break;
        }
    }

    return 0;
}
