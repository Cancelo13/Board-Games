#ifndef PYRAMID_X_O_H
#define PYRAMID_X_O_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include <cstdlib>
#include <ctime>

using namespace std;

// Pyramid Tic-Tac-Toe Board Class
template <typename T>
class Pyramid_Board : public Board<T> {
public:
    Pyramid_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

// Pyramid Player Class
template <typename T>
class Pyramid_Player : public Player<T> {
public:
    Pyramid_Player(string name, T symbol);
    void getmove(int& x, int& y);
};

// Pyramid Random Player Class
template <typename T>
class Pyramid_Random_Player : public RandomPlayer<T> {
public:
    Pyramid_Random_Player(T symbol);
    void getmove(int& x, int& y);
};

//--------------------------------------- IMPLEMENTATION

// Constructor for Pyramid_X_O_Board
template <typename T>
Pyramid_Board<T>::Pyramid_Board() {
    this->rows = 3;
    this->columns = 5;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;  // Initialize all cells as empty
        }
    }
    this->n_moves = 0;
}

// Update board for valid pyramid moves
template <typename T>
bool Pyramid_Board<T>::update_board(int x, int y, T mark) {
    // Check if the move is valid within the pyramid layout
    if ((x == 0 && y == 2) ||
        (x == 1 && (y >= 1 && y <= 3)) ||
        (x == 2 && (y >= 0 && y <= 4))) {
        if (this->board[x][y] == 0 || mark == 0) {
            if (mark == 0) {
                this->n_moves--;
                this->board[x][y] = 0;
            } else {
                this->n_moves++;
                this->board[x][y] = toupper(mark);
            }
            return true;
        }
    }
    return false;
}

// Display the pyramid board
template <typename T>
void Pyramid_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n";
        for (int j = 0; j < this->columns; j++) {
            if ((i == 0 && j == 2) ||
                (i == 1 && (j ==1 || j==2 || j==3 )) ||
                (i == 2 && (j ==0|| j==1 || j==2 || j==3 || j==4))) {
                cout << " |(" << i << "," << j << ")|";
                cout << setw(2) << this->board[i][j] ;
            } else {
                cout << "      ";  // Skip invalid cells
            }
        }
        cout << "\n---------------------------------";
    }
    cout << endl;
}

// Check for a win in pyramid layout
template <typename T>
bool Pyramid_Board<T>::is_win() {
    // Check rows
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns - 2; j++) {
            if (this->board[i][j] != 0 &&
                this->board[i][j] == this->board[i][j + 1] &&
                this->board[i][j + 1] == this->board[i][j + 2]) {
                return true;
            }
        }
    }

    // Check columns
    for (int j = 0; j < this->columns; j++) {
        for (int i = 0; i < this->rows - 2; i++) {
            if (this->board[i][j] != 0 &&
                this->board[i][j] == this->board[i + 1][j] &&
                this->board[i + 1][j] == this->board[i + 2][j]) {
                return true;
            }
        }
    }

    // Check diagonals
    for (int i = 0; i < this->rows - 2; i++) {
        for (int j = 0; j < this->columns - 2; j++) {
            if (this->board[i][j] != 0 &&
                this->board[i][j] == this->board[i + 1][j + 1] &&
                this->board[i + 1][j + 1] == this->board[i + 2][j + 2]) {
                return true;
            }
            if (this->board[i][j + 2] != 0 &&
                this->board[i][j + 2] == this->board[i + 1][j + 1] &&
                this->board[i + 1][j + 1] == this->board[i + 2][j]) {
                return true;
            }
        }
    }
    return false;
}

// Check for a draw
template <typename T>
bool Pyramid_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool Pyramid_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

// Constructor for Pyramid_X_O_Player
template <typename T>
Pyramid_Player<T>::Pyramid_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Pyramid_Player<T>::getmove(int& x, int& y) {
    string xval , yval;
    while(true) {
        cout << "\nEnter your move (row and column): ";
        cin >> xval >> yval;
        try {
            x = stoi(xval);
            y = stoi(yval);
            break;
        }
        catch(...) {
            cout << "Invalid input!" << endl;
        }
    }
}

// Constructor for Pyramid_X_O_Random_Player
template <typename T>
Pyramid_Random_Player<T>::Pyramid_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void Pyramid_Random_Player<T>::getmove(int& x, int& y) {
    // Valid moves for the pyramid layout
    int valid_moves[9][2] = {
        {0, 2}, {1, 1}, {1, 2}, {1, 3},
        {2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4}
    };

    // Pick a random index from valid_moves
    int random_index = rand() % 9;  // Randomly pick an index from 0 to 8
    x = valid_moves[random_index][0];  // Get the row from valid_moves
    y = valid_moves[random_index][1];  // Get the column from valid_moves

}

#endif // PYRAMID_X_O_H
