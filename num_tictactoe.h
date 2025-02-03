#ifndef NUMXO_H
#define NUMXO_H
#include "BoardGame_Classes.h"
#include <bits/stdc++.h>
using namespace std;


bool is_p1_human= false , is_p2_human= false ;
static vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};

class Tictactoe : public Board<int> {
    public: Tictactoe() { this->rows = 3; this->columns = 3;
        this->board = new int*[this->rows];
        for (int i = 0; i < this->rows; i++) {
            this->board[i] = new int[this->columns];
            for (int j = 0; j < this->columns; j++) {
                this->board[i][j] = 0;
            }
        }
        this->n_moves = 0;
    }

    bool update_board(int x, int y, int number)  {
        if (y < 0 || y >= this->columns || x < 0 || x >= this->rows || this->board[x][y] != 0) {
            return false;
        }
        int num = getNum(); // Obtain number from player
        this->board[x][y] = num;
        this->n_moves++;
        return true;
    }

    void display_board() {
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
    int getNum(){
        int num;
        if(is_p1_human==true && n_moves % 2 == 0){//human player1
            while (true){
                cout << "Enter odd number: ";
                cin >> num;
                if (!cin.fail() && num >= 1 && num <= 9 && nums[num - 1] != 0 && nums[num - 1] % 2 != 0) {
                    nums[num - 1] = 0;
                    return num;
                } else {
                    cout << "Error,Please enter an odd number between 1 and 9 that hasn't been chosen before.\n";
                }
            }
        }
        else if(is_p2_human== true && n_moves%2!=0){//human player2
            while(true){
                cout << "Enter even number: ";
                cin >> num;
                if (!cin.fail() && num >= 1 && num <= 9 && nums[num - 1] != 0 && nums[num - 1] % 2 == 0) {
                    nums[num - 1] = 0;
                    return num;
                } else {
                    cout << "Error,Please enter an even number between 1 and 9 that hasn't been chosen before.\n";
                }
            }
        }
        else{//Random part
            set<int> valid_numbers;
            if (is_p1_human == false && n_moves % 2 == 0) { // Random player 1
                for (int i = 1; i <= 9; i += 2) { // Odd numbers
                    if (nums[i - 1] != 0) {
                        valid_numbers.insert(i);
                    }
                }
            } else if (is_p2_human == false && n_moves % 2 != 0) { // Random player 2
                for (int i = 2; i <= 9; i += 2) { // Even numbers
                    if (nums[i - 1] != 0) {
                        valid_numbers.insert(i);
                    }
                }
            }

            if (!valid_numbers.empty()) {
                auto it = valid_numbers.begin();
                advance(it, rand() % valid_numbers.size());
                num = *it;
                nums[num - 1] = 0; // Mark number as used
            }
        }
//        cin.clear();
//        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return num;
    }

    bool is_win() {
        // Check horizontal lines
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns - 2; j++) {
                if (this->board[i][j] != 0 && this->board[i][j + 1] != 0 && this->board[i][j + 2] != 0 &&
                    this->board[i][j] + this->board[i][j + 1] + this->board[i][j + 2] == 15) {
                    return true;
                }
            }
        }

        // Check vertical lines
        for (int i = 0; i < this->rows - 2; i++) {
            for (int j = 0; j < this->columns; j++) {
                if (this->board[i][j] != 0 && this->board[i + 1][j] != 0 && this->board[i + 2][j] != 0 &&
                    this->board[i][j] + this->board[i + 1][j] + this->board[i + 2][j] == 15) {
                    return true;
                }
            }
        }

        // Check diagonal (top-left to bottom-right)
        for (int i = 0; i < this->rows - 2; i++) {
            for (int j = 0; j < this->columns - 2; j++) {
                if (this->board[i][j] != 0 && this->board[i + 1][j + 1] != 0 && this->board[i + 2][j + 2] != 0 &&
                    this->board[i][j] + this->board[i + 1][j + 1] + this->board[i + 2][j + 2] == 15) {
                    return true;
                }
            }
        }

        // Check diagonal (bottom-left to top-right)
        for (int i = 2; i < this->rows; i++) {
            for (int j = 0; j < this->columns - 2; j++) {
                if (this->board[i][j] != 0 && this->board[i - 1][j + 1] != 0 && this->board[i - 2][j + 2] != 0 &&
                    this->board[i][j] + this->board[i - 1][j + 1] + this->board[i - 2][j + 2] == 15) {
                    return true;
                }
            }
        }
        return false;
    }

    bool is_draw() {
        return (this->n_moves == 9 && !is_win());
    }

    bool game_is_over() {
        return is_win() || is_draw();
    }
};

class Tictactoe_Player : public Player<int> {
public:
    Tictactoe_Player(string name, int symbol) : Player(name, symbol) {}
    void getmove(int& x, int& y) {
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

class Tictactoe_RandomPlayer : public RandomPlayer<int> {
public:
    Tictactoe_RandomPlayer(int num) : RandomPlayer(num) {
        this->dimension = 3;
        this->name = "Random Computer Player";
        srand(static_cast<unsigned int>(time(0))); // Seed for randomness
    }

    void getmove(int& x, int& y)  {
        x = rand() % this->dimension;
        y = rand() % this->dimension;
    }

};

#endif //NUMXO_H
