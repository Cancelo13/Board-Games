#ifndef SUS_H
#define SUS_H
#include "BoardGame_Classes.h"
#include <bits/stdc++.h>
using namespace std;

int temp=0 ;
int nmoves;
template<typename T>
class Sus : public Board<char> {
private:
    int p1_score ,p2_score ;
public:
    Sus(){
        this->rows = 3; this->columns = 3;
        this->board = new char *[this->rows];
        for (int i = 0; i < this->rows; i++) {
            this->board[i] = new char [this->columns];
            for (int j = 0; j < this->columns; j++) {
                this->board[i][j] = 0;
            }
        }
        this->n_moves = 0;
        p1_score = 0;
        p2_score = 0;
        nmoves = 0;
    }

    void check_sus(int i, int j) {
        int numofsus=0;
        // Check for winning conditions: horizontal, vertical, and diagonal "SUS"
        if ((this->board[0][0] == 'S' && this->board[0][1] == 'U' && this->board[0][2] == 'S')) {
            numofsus++;
        }
        if(this->board[1][0] == 'S' && this->board[1][1] == 'U' && this->board[1][2] == 'S') {
            numofsus++;
        }
        if(this->board[2][0] == 'S' && this->board[2][1] == 'U' && this->board[2][2] == 'S') {
            numofsus++;
        }
        if(this->board[0][0] == 'S' && this->board[1][0] == 'U' && this->board[2][0] == 'S') {
            numofsus++;
        }
        if(this->board[0][1] == 'S' && this->board[1][1] == 'U' && this->board[2][1] == 'S') {
            numofsus++;
        }
        if(this->board[0][2] == 'S' && this->board[1][2] == 'U' && this->board[2][2] == 'S') {
            numofsus++;
        }
        if(this->board[0][0] == 'S' && this->board[1][1] == 'U' && this->board[2][2] == 'S') {
            numofsus++;
        }
        if(this->board[0][2] == 'S' && this->board[1][1] == 'U' && this->board[2][0] == 'S') {
            numofsus++;
        }
        if (n_moves % 2) {
            p1_score += (((numofsus - temp) > 0) ? (numofsus - temp) : 0);
        }
        else{
            p2_score += (((numofsus - temp) > 0)?(numofsus - temp) : 0);
        }
        temp=numofsus;
        cout<<"  \np1 score: "<<p1_score<<"   p2 score: "<<p2_score<<"\n";
    }

    bool can_sus() {

        // Check rows for possible "SUS"
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j <= columns - 3; ++j) { // Ensure valid index range
                if ((board[i][j] == 'S' || board[i][j] == 0) &&
                    (board[i][j + 1] == 'U' || board[i][j + 1] == 0) &&
                    (board[i][j + 2] == 'S' || board[i][j + 2] == 0)) {
                    return true;
                }
            }
        }

        // Check columns for possible "SUS"
        for (int j = 0; j < columns; ++j) {
            for (int i = 0; i <= rows - 3; ++i) { // Ensure valid index range
                if ((board[i][j] == 'S' || board[i][j] == 0) &&
                    (board[i + 1][j] == 'U' || board[i + 1][j] == 0) &&
                    (board[i + 2][j] == 'S' || board[i + 2][j] == 0)) {
                    return true;
                }
            }
        }

        // Check main diagonal for possible "SUS"
        for (int i = 0; i <= rows - 3; ++i) {
            for (int j = 0; j <= columns - 3; ++j) { // Ensure valid index range
                if ((board[i][j] == 'S' || board[i][j] == 0) &&
                    (board[i + 1][j + 1] == 'U' || board[i + 1][j + 1] == 0) &&
                    (board[i + 2][j + 2] == 'S' || board[i + 2][j + 2] == 0)) {
                    return true;
                }
            }
        }

        // Check anti-diagonal for possible "SUS"
        for (int i = 0; i <= rows - 3; ++i) {
            for (int j = 2; j < columns; ++j) { // Start from the third column
                if ((board[i][j] == 'S' || board[i][j] == 0) &&
                    (board[i + 1][j - 1] == 'U' || board[i + 1][j - 1] == 0) &&
                    (board[i + 2][j - 2] == 'S' || board[i + 2][j - 2] == 0)) {
                    return true;
                }
            }
        }

        // If no possible "SUS" is found
        return false;
    }
    bool update_board(int x, int y, char symbol){
        if(nmoves == 9) {
            return true;
        }
        if (y < 0 || y >= this->columns || x < 0 || x >= this->rows || this->board[x][y] != 0) {
            return false;
        }
        this->board[x][y] = symbol;
        this->n_moves++;
        nmoves++;
        check_sus(x,y);
        return true;
    }
    void display_board(){
        cout << "\n";
        for (int j = 0; j < this->columns; j++) {
            cout << "   " << j << "  ";
        }
        cout << "\n  ------------------";
        for (int i = 0; i < this->rows; i++) {
            cout << "\n"<<i<<"|";
            for (int j = 0; j < this->columns; j++) {
                if (this->board[i][j] != 0) {
                    cout << "  " << this->board[i][j] << "  |";
                } else {
                    cout << "     |";
                }
            }
            cout << "\n  ------------------";
        }
        cout << endl;
    }
    bool wining(){
        if(n_moves==9 || !can_sus()){
            if(!can_sus()) {
                cout<<"No more SUS"<<endl;
            }
            return true;
        }
        return false;
    }
    int Get_P1Score() {
        return p1_score;
    }
    int Get_P2score() {
        return p2_score;
    }
    bool is_win(){
        return false;
    }
    bool is_draw(){
        return n_moves == 9 && !wining();
    }
    bool game_is_over(){
        return n_moves==9 || !can_sus();
    }
};

template<typename T>
class Sus_Player : public Player<char> {
public:
    Sus_Player(string name, char symbol): Player(name, symbol) {}
    void getmove(int& x, int& y) {
        if(nmoves == 9) {
            return;
        }
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

template<typename T>
class Sus_RandomPlayer : public RandomPlayer<char> {
public:
    Sus_RandomPlayer(char symbol): RandomPlayer(symbol){
        this->dimension = 3;
        this->name = "Random Computer Player";
        srand(static_cast<unsigned int>(time(0))); // Seed for randomness
    }
    void getmove(int& x, int& y){
        if(nmoves == 9) {
            return;
        }
        x = rand() % this->dimension;
        y = rand() % this->dimension;
    }
};

#endif //SUS_H
