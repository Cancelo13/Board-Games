#ifndef INVERSEXO_H
#define INVERSEXO_H


#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype>
using namespace std;

template <typename T>
class InverseXO : public Board<T> {
public:
    InverseXO() {
        this->rows = this->columns = 3;
        this->board = new char*[this->rows];
        for (int i = 0; i < this->rows; i++) {
            this->board[i] = new char[this->columns];
            for (int j = 0; j < this->columns; j++) {
                this->board[i][j] = 0;
            }
        }
        this->n_moves = 0;
    }
    bool update_board (int x , int y , T mark)
    {
        // Only update if move is valid
        if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
            if (mark == 0){
                this->n_moves--;
                this->board[x][y] = 0;
            }
            else {
                this->n_moves++;
                this->board[x][y] = toupper(mark);
            }

            return true;
        }
        return false;
    }
    void display_board ()
    {
        for (int i = 0; i < this->rows; i++) {
            cout << "\n| ";
            for (int j = 0; j < this->columns; j++) {
                cout << "(" << i << "," << j << ")";
                cout << setw(2) << this->board[i][j] << " |";
            }
            cout << "\n-----------------------------";
        }
        cout << endl;
    }
    bool Check(int x, int y , T symbol) {
        if (symbol != 'X' && symbol != 'O')
        {
            return false;
        }
        if(this->board[x][y] != symbol)
        {
            return false;
        }
        if (y + 2 < this->columns  && this->board[x][y + 1] == symbol && this->board[x][y + 2] == symbol)
            {
            return true;
        }
        if (x + 2 < this->rows && this->board[x + 1][y] == symbol && this->board[x + 2][y] == symbol)
        {
            return true;
        }
        if (x + 2 < this->rows && y + 2 < this->columns && this->board[x + 1][y + 1] == symbol && this->board[x + 2][y + 2] == symbol)
        {
            return true;
        }
        if (y - 2 >= 0 && x + 2 < this->rows && this->board[x + 1][y - 1] == symbol && this->board[x + 2][y - 2] == symbol)
        {
            return true;
        }
        return false;
    }
    bool is_win()
    {
        for(int i = 0 ; i < this->rows ; i++) {
            for(int j = 0 ; j < this->columns ; j++) {
                if(Check(i , j , this->board[i][j])) {
                    return true;
                }
            }
        }
        return false;
    }
    bool is_draw()
    {
        return this->n_moves == 9;
    }
    bool game_is_over()
    {
        return is_draw() || is_win();
    }

};
template <typename T>
class InverseX_O_Player : public Player<T> {
public:
    InverseX_O_Player (string name, T symbol): Player<T>(name, symbol) {};
    void getmove(int& x, int& y)
    {
        string xval , yval;
        while(true) {
            cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
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

};
template <typename T>
class InverseX_O_Random_Player : public RandomPlayer<T>{
public:
    InverseX_O_Random_Player (T symbol) :RandomPlayer<T>(symbol) {
        this->dimension = 3;
        this->name = "Random Computer Player";
        srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
    };
    void getmove(int &x, int &y)
    {
        x = rand() % this->dimension;  // Random number between 0 and 5
        y = rand() % this->dimension;
    }
};


#endif //INVERSEXO_H
