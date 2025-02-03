#ifndef FOURINROW_H
#define FOURINROW_H
#include "BoardGame_Classes.h"
#include <bits/stdc++.h>
using namespace std;

class FourinRow :public Board<char>{
public:
    FourinRow(){
        this->rows =6;
        this->columns = 7;

        this->board = new char*[this->rows];
        for (int i = 0; i < this->rows; i++) {
            this->board[i] = new char[this->columns];
            for (int j = 0; j < this->columns; j++) {
                this->board[i][j] = 0;
            }
        }
        this->n_moves = 0;
    }

    bool update_board(int x, int y, char mark) {
        if (y < 0 || y >= this->columns) return false; // Check if the column is valid
        // Find the lowest available row in the column
        for (int i = this->rows - 1; i >= 0; i--) {
            if (this->board[i][y] == 0) {
                this->board[i][y] = toupper(mark); // Place the piece
                this->n_moves++;
                return true;
            }
        }
        return false; // Column is full
    }

    void display_board() {
        cout << "\n";
        for (int j = 0; j < this->columns; j++) {
            cout <<"   "<<j + 1 <<"  ";  // Adjust column number width for alignment
        }
        cout << "\n--------------------------------------------";
        for (int i = 0; i < this->rows; i++) {
            cout << "\n|";
            for (int j = 0; j < this->columns; j++) {
                if (this->board[i][j] != 0) {
                    cout << "  " << this->board[i][j] << "  |";
                } else {
                    cout << "     |";
                }
            }
            cout << "\n--------------------------------------------";
        }
        cout << endl;
    }


    // Returns true if there is any winner
    bool is_win() {
        // Check horizontal lines
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j <= this->columns - 4; j++) {
                if (this->board[i][j] != 0 &&
                    this->board[i][j] == this->board[i][j + 1] &&
                    this->board[i][j] == this->board[i][j + 2] &&
                    this->board[i][j] == this->board[i][j + 3]) {
                    return true;
                }
            }
        }
        // Check vertical lines
        for (int i = 0; i <= this->rows - 4; i++) {
            for (int j = 0; j < this->columns; j++) {
                if (this->board[i][j] != 0 &&
                    this->board[i][j] == this->board[i + 1][j] &&
                    this->board[i][j] == this->board[i + 2][j] &&
                    this->board[i][j] == this->board[i + 3][j]) {
                    return true;
                }
            }
        }
        // Check diagonal (bottom-left to top-right)
        for (int i = 0; i <= this->rows - 4; i++) {
            for (int j = 0; j <= this->columns - 4; j++) {
                if (this->board[i][j] != 0 &&
                    this->board[i][j] == this->board[i + 1][j + 1] &&
                    this->board[i][j] == this->board[i + 2][j + 2] &&
                    this->board[i][j] == this->board[i + 3][j + 3]) {
                    return true;
                }
            }
        }
        // Check diagonal (top-left to bottom-right)
        for (int i = 3; i < this->rows; i++) {
            for (int j = 0; j <= this->columns - 4; j++) {
                if (this->board[i][j] != 0 &&
                    this->board[i][j] == this->board[i - 1][j + 1] &&
                    this->board[i][j] == this->board[i - 2][j + 2] &&
                    this->board[i][j] == this->board[i - 3][j + 3]) {
                    return true;
                }
            }
        }
        return false;
    }

    bool is_draw(){
        return (this->n_moves == 42 && !is_win());
    }
    bool game_is_over(){
        return is_win() || is_draw();
    }
};

class FourinRow_player : public Player<char> {
public:
    FourinRow_player(string name, char symbol) : Player(name, symbol) {}

    void getmove(int& x, int& y) {
        string xval , yval;
        while(true) {
            cout << "\nEnter column (1 to 7): ";
            cin >> yval;
            try {
                y = stoi(yval);
                break;
            }
            catch(...) {
                cout << "Invalid input!" << endl;
            }
        }
        y--;
        x = -1; // Not used
    }
};


class FourinRow_RandomPlayer : public  RandomPlayer<char>{
public:
    FourinRow_RandomPlayer(char mark): RandomPlayer(mark){
        this->dimension = 7;
        this->name = "Random Computer Player";
        srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
    }
    void getmove(int &x, int &y) {
        x = rand() % this->dimension;
        y = rand() % this->dimension-1;
    }


};

#endif //FOURINROW_H
