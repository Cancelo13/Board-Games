#ifndef WORDXO_H
#define WORDXO_H

#include "BoardGame_Classes.h"
const string DIC_FILE_PATH = "../dic.txt";
bool p1human= false , p2human= false ;

template <typename T>
class Word_Board:public Board<T> {
public:
    Word_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    char getchar();

};

template <typename T>
class Word_Player : public Player<T> {
public:
    Word_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};
template <typename T>
class Word_Random_Player : public RandomPlayer<T>{
public:
    Word_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};
//--------------------------------------------------------------------------- implementation of the functions


#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include <fstream>
#include <string>

using namespace std;

// Function to check if a word is valid by reading dic.txt
bool is_valid_word(const string& word) {
    ifstream dic_file(DIC_FILE_PATH); // Open the dictionary file
    if (!dic_file) {
        cout << "Error opening dictionary file.\n";
        return false;
    }

    string dic_word;
    while (getline(dic_file, dic_word)) {
        // Check if the word in dic.txt matches the input word (case-insensitive)
        if (dic_word == word) {
            dic_file.close();
            return true;
        }
    }

    dic_file.close();
    return false; // Return false if no match is found
}

// Constructor for X_O_Board
template <typename T>
Word_Board<T>::Word_Board() {
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
template <typename T>
bool Word_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if ((x < 0 || x >= this->rows || y < 0 || y >= this->columns || (this->board[x][y] != 0))) return false;

    mark = Word_Board::getchar();
    this->n_moves++;
    this->board[x][y] = toupper(mark);

    return true;
}

template <typename T>
char Word_Board<T>::getchar() {
    char letter;
    if(p1human== true && Word_Board::n_moves %2==0){
        cout<<"Enter a letter:"<<endl;
        cin>>letter;
    }
    if(p1human== false && Word_Board::n_moves %2==0){
        letter = 'A'+ rand()%26;
    }
    if(p2human== true && Word_Board::n_moves %2!=0){
        cout<<"Enter a letter:"<<endl;
        cin>>letter;
    }
    if(p2human== false && Word_Board::n_moves %2!=0){
        letter = 'A'+ rand()%26;
    }
    return letter;
}




// Display the board and the pieces on it
template <typename T>
void Word_Board<T>::display_board() {
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

// Returns true if there is any winner
template <typename T>
bool Word_Board<T>::is_win() {
    for (int i = 0; i < this->rows; ++i) {
        string row_word, col_word;
        for (int j = 0; j < this->columns; ++j) {
            row_word += this->board[i][j];
            col_word += this->board[j][i];
        }
        if (is_valid_word(row_word) || is_valid_word(col_word)) {
            return true;
        }
    }

    string diag1_word, diag2_word;
    for (int i = 0; i < this->rows; ++i) {
        diag1_word += this->board[i][i];
        diag2_word += this->board[i][this->columns - 1 - i];
    }

    return is_valid_word(diag1_word) || is_valid_word(diag2_word);
}


// Return true if 9 moves are done and no winner
template <typename T>
bool Word_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool Word_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
Word_Player<T>::Word_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Word_Player<T>::getmove(int& x, int& y) {
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

// Constructor for X_O_Random_Player
template <typename T>
Word_Random_Player<T>::Word_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}


template <typename T>
void Word_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}


#endif //WORDXO_H
