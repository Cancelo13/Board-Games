#ifndef ULTIMATEXO_H
#define ULTIMATEXO_H
#include "BoardGame_Classes.h"


template <typename T>
class UltimateTicTacToeBoard : public Board<T> {
private:
    vector<vector<char>> Mainboard;
public:
    UltimateTicTacToeBoard() {
        this->rows = 9;
        this->columns = 9;
        Mainboard = vector(3, vector(3 , ' '));
        this->board = new char*[this->rows];
        for (int i = 0; i < this->rows; i++) {
            this->board[i] = new char[this->columns];
            for (int j = 0; j < this->columns; j++) {
                this->board[i][j] = 0;
            }
        }
        this->n_moves = 0;
    }
    bool update_board(int x , int y , T mark) {
        if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
            if (mark == 0){
                --this->n_moves;
                this->board[x][y] = 0;
            }
            else {
                ++this->n_moves;
                this->board[x][y] = toupper(mark);
                update_Mainboard();
            }
            return true;
        }
        return false;
    }
    void display_board() {
        cout<<"Board of Boards: "<<endl;
        for (int i = 0; i < this->rows; i++) {
            cout << "\n| ";
            for (int j = 0; j < this->columns; j++) {
                cout << "(" << i << "," << j << ")";
                cout << setw(2) << this->board[i][j] << " |";
            }
            cout << "\n-----------------------------";
        }
        cout << endl;
        cout<< "Main Board: "<<endl;
        for(int i = 0 ; i < 3 ; i++) {
            cout <<"\n| ";
            for(int j = 0 ; j < 3 ; j++) {
                cout << setw(2) << Mainboard[i][j] << " |";
            }
            cout<< "\n-----------------------------";
        }
        cout<<endl;
    }
    bool Check(int x, int y , T symbol , int lbx , int lby) {
        if (symbol != 'X' && symbol != 'O')
        {
            return false;
        }
        if(this->board[x][y] != symbol)
        {
            return false;
        }
        if (y + 2 < lby + 3 && this->board[x][y + 1] == symbol && this->board[x][y + 2] == symbol)
        {
            return true;
        }
        if (x + 2 < lbx + 3 && this->board[x + 1][y] == symbol && this->board[x + 2][y] == symbol)
        {
            return true;
        }
        if (x + 2 < lbx + 3 && y + 2 < lby + 3 && this->board[x + 1][y + 1] == symbol && this->board[x + 2][y + 2] == symbol)
        {
            return true;
        }
        if (y - 2 >= lby && x + 2 < lbx + 3 && this->board[x + 1][y - 1] == symbol && this->board[x + 2][y - 2] == symbol)
        {
            return true;
        }
        return false;
    }
    char check_sub_board(int x , int y) {
        for(int i = x ; i < x + 3 ; i++) {
            for(int j = y ; j < y + 3 ; j++) {
                if(Check(i , j , this->board[i][j] , x , y)) {
                    return this->board[i][j];
                }
            }
        }
        return 'F';
    }
    void update_Mainboard() {
        for(int i = 0 ; i <= 6 ; i += 3) {
            for(int j = 0 ;j <= 6 ; j+= 3) {
                char t = check_sub_board(i, j);
                if( t != 'F') {
                    if(Mainboard[i / 3][j / 3] != 'X' && Mainboard[i / 3][j / 3] != 'O') {
                        Mainboard[i / 3][j / 3] = t;
                    }
                }
            }
        }
    }
    bool CheckMainBoard(int x , int y , T symbol) {
        if (symbol != 'X' && symbol != 'O')
        {
            return false;
        }
        if(Mainboard[x][y] != symbol)
        {
            return false;
        }
        if (y + 2 < 3  && Mainboard[x][y + 1] == symbol && Mainboard[x][y + 2] == symbol)
        {
            return true;
        }
        if (x + 2 < 3 && Mainboard[x + 1][y] == symbol && Mainboard[x + 2][y] == symbol)
        {
            return true;
        }
        if (x + 2 < 3 && y + 2 < 3 && Mainboard[x + 1][y + 1] == symbol && Mainboard[x + 2][y + 2] == symbol)
        {
            return true;
        }
        if (y - 2 >= 0 && x + 2 < 3 && Mainboard[x + 1][y - 1] == symbol && Mainboard[x + 2][y - 2] == symbol)
        {
            return true;
        }
        return false;
    }
    bool is_win() {
        for(int i = 0 ; i < 3 ; i++) {
            for(int j = 0 ; j < 3 ; j++) {
                if(CheckMainBoard(i , j , Mainboard[i][j])) {
                    return true;
                }
            }
        }
        return false;
    }
    bool is_draw() {
        return this->n_moves == 81;
    }
    bool game_is_over() {
         return is_draw()|| is_win();
    }

};
template<typename T>
class UltimateXO_Player : public Player<T> {
public:
    UltimateXO_Player(string name, T symbol): Player<T>(name, symbol) {};
    void getmove(int& x, int& y)
    {
        string xval , yval;
        while(true) {
            cout << "\nPlease enter your move x and y (0 to 8) separated by spaces: ";
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
class UltimateRandom_Player : public RandomPlayer<T> {
public:
     UltimateRandom_Player(T symbol): RandomPlayer<T>(symbol) {
        this->dimension = 9;
        this->name = "Random Computer Player";
        srand(static_cast<unsigned int>(time(0)));
    };
    void getmove(int& x, int& y) {
        x = rand() % 8;
        y = rand() % 8;
    }

};


#endif //ULTIMATEXO_H
