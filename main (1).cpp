#include <iostream>
#include "BoardGame_Classes.h"
#include "X_O_5x5.h"
#include "InverseXO.h"
#include "SUS.h"
#include "UltimateXO.h"
#include "fourinrow.h"
#include "numxo.h"
#include "pyramic_XO.h"
#include "wordxo.h"
using namespace std;

void RunApp();
void Run_Pyrmic_XO();
void Run_four_inarow();
void Run_xo5x5();
void Run_WordXO();
void Run_NumericalXO();
void Run_InverseXO();
void Run_UXO();
void Run_SUS();

//=======================================================//
int main() {
    RunApp();
    return 0;
}
//=======================================================//
void RunApp() {
    while(true) {
        cout << "Welcome to Tic Tac Toe Board Games"<<endl;
        cout<<"================================================="<<endl;
        cout<<"Games List:"<<endl;
        cout<<"============="<<endl;
        cout<<"1)Pyramic Tic-Tac-Toe"<<endl<<"2)Four in a row"<<endl<<"3)5x5 TicTacToe"<<endl<<"4)Word Ti-Tac-Toe"<<endl
        <<"5)Numerical Tic-Tac-Toe"<<endl<<"6)Misere Tic-Tac-Toe"<<endl<<"7)Ultimate Tic-Tac-Toe"<<endl<<"8)SUS"<<endl
        <<"9)Exit The Program"<<endl;
        string game_num ;
        cout<<"Please Choose a game by entering the corresponding number: ";
        cin>>game_num;
        cout<<endl;
        if(game_num == "1") {
            Run_Pyrmic_XO();
        }
        else if(game_num == "2") {
            Run_four_inarow();
        }
        else if(game_num == "3") {
            Run_xo5x5();
        }
        else if(game_num == "4") {
            Run_WordXO();
        }
        else if(game_num == "5") {
            Run_NumericalXO();
        }
        else if(game_num == "6") {
            Run_InverseXO();
        }
        else if(game_num == "7") {
            Run_UXO();
        }
        else if(game_num == "8") {
            Run_SUS();
        }
        else if(game_num == "9") {
            cout<<"Thanks for playing!"<<endl;
            break;
        }
        else {
            cout<<"Game number not recognized"<<endl;
        }
    }

}
//====//
void Run_Pyrmic_XO() {
    bool game = true;
    while(game) {
        string choice;
        Player<char>* players[2];
        auto* B = new Pyramid_Board<char>();
        string player_1_Name, player_2_Name;
        cout << "Enter first Player name: ";
        cin >> player_1_Name;
        while(true)
        {
            cout << "Types List:"<<endl;
            cout << "1)Human"<<endl<<"2)Random Computer"<<endl;
            cout << "Choose first Player type: ";
            cin >> choice;
            cout<<endl;
            if(choice == "1")
            {
                players[0] = new Pyramid_Player<char>(player_1_Name, 'X');
                break;
            }
            if(choice == "2")
            {
                players[0] = new Pyramid_Random_Player<char>('X');
                break;
            }
            cout << "Invalid choice ";
        }
        // Set up player 2
        cout << "Enter Player 2 name: ";
        cin >> player_2_Name;
        while(true)
        {
            cout << "Types List:"<<endl;
            cout << "1)Human"<<endl<<"2)Random Computer"<<endl;
            cout << "Choose first Player type: ";
            cin >> choice;
            cout<<endl;
            if(choice == "1")
            {
                players[1] = new Pyramid_Player<char>(player_2_Name, 'O');
                break;
            }
            if(choice == "2")
            {
                players[1] = new Pyramid_Random_Player<char>('O');
                break;
            }
            cout << "Invalid choice ";
        }
        GameManager<char> x_o_game(B, players);
        x_o_game.run();
        delete B;
        for (auto & player : players) {
            delete player;
        }
        while(true) {
            cout<<"Do you want to play again ? (y/n)"<<endl;
            string answer;
            cin>>answer;
            if(answer == "y" || answer == "Y") {
                break;
            }
            if(answer == "n" || answer == "N") {
                cout<<"Thanks for playing, have a nice day <3"<<endl;
                game = false;
                break;
            }
            cout<<"Wrong option, Please try again"<<endl;
        }
    }

}
//====//
void Run_four_inarow() {
    cout << "     ---- Welcome to 4-in-Row Game ----\n\n";

    while (true) {
        Player<char>* players[2];
        FourinRow* board = new FourinRow();
        string playerXName, playerOName;

        //Player 2 setup
        cout << "Enter Player X name: ";
        cin >> playerXName;
        cout << "Choose Player X type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        int choice;
        cin >> choice;

        if (choice == 1) {
            players[0] = new FourinRow_player(playerXName, 'X');
        } else if (choice == 2) {
            players[0] = new FourinRow_RandomPlayer('X');
        } else {
            cout << "Invalid choice. Restarting...\n";
            delete board;
            continue;
        }
        players[0]->setBoard(board);

        // Player 2 setup
        cout << "Enter Player O name: ";
        cin >> playerOName;
        cout << "Choose Player O type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;

        if (choice == 1) {
            players[1] = new FourinRow_player(playerOName, 'O');
        } else if (choice == 2) {
            players[1] = new FourinRow_RandomPlayer('O');
        } else {
            cout << "Invalid choice. Restarting...\n";
            delete players[0];
            delete board;
            continue;
        }
        players[1]->setBoard(board);

        GameManager<char> manager(board, players);
        manager.run();

        delete board;
        delete players[0];
        delete players[1];

        cout << "\nDo you want to play again? (y/n): ";
        char Choice;
        cin >> Choice;
        if (tolower(Choice) != 'y') {
            cout << "Goodbye!\n";
            break;
        }
    }
}
//====//
void Run_xo5x5() {
    bool game = true;
    while(game) {
        string choice;
        Player<char>* players[2];
        auto* B = new X_O_5x5_Board<char>();
        string player_1_Name, player_2_Name;
        cout << "Enter first Player name: ";
        cin >> player_1_Name;
        while(true)
        {
            cout << "Types List:"<<endl;
            cout << "1)Human"<<endl<<"2)Random Computer"<<endl;
            cout << "Choose first Player type: ";
            cin >> choice;
            cout<<endl;
            if(choice == "1")
            {
                players[0] = new X_O_Player<char>(player_1_Name, 'X');
                break;
            }
            if(choice == "2")
            {
                players[0] = new X_O_Random_Player<char>('X');
                break;
            }
            cout << "Invalid choice ";
        }
        cout << "Enter second Player name: ";
        cin >> player_2_Name;
        while(true)
        {
            cout << "Types List:"<<endl;
            cout << "1)Human"<<endl<<"2)Random Computer"<<endl;
            cout << "Choose first Player type: ";
            cin >> choice;
            cout << endl;
            if(choice == "1")
            {
                players[1] = new X_O_Player<char>(player_2_Name, 'O');
                break;
            }
            if(choice == "2")
            {
                players[1] = new X_O_Random_Player<char>('O');
                break;
            }
            cout << "Invalid choice ";
        }
        GameManager<char> x_o_game(B, players);
        x_o_game.run();
        int scoreX =  B->Get_score(players[0]->getsymbol());
        int scoreO = B->Get_score(players[1]->getsymbol());
        cout<<"=============================="<<endl;
        if(scoreX > scoreO) {
            cout << players[0]->getname() <<" wins!\n";
        }
        else if(scoreX < scoreO) {
            cout <<players[1]->getname() <<" wins!\n";
        }
        else {
            cout<<"It's a draw!\n";
        }
        cout<<"=============================="<<endl;
        cout<<"Scores Table: " << endl <<players[0]->getname()<<" = "<<scoreX<<endl<<players[1]->getname()<<" = "<<scoreO<<"\n";
        cout<<"=============================="<<endl;
        // Clean up
        delete B;
        for (auto & player : players) {
            delete player;
        }
        while(true) {
            cout<<"Do you want to play again ? (y/n)"<<endl;
            string answer;
            cin>>answer;
            if(answer == "y" || answer == "Y") {
                break;
            }
            if(answer == "n" || answer == "N") {
                cout<<"Thanks for playing, have a nice day <3"<<endl;
                game = false;
                break;
            }
            cout<<"Wrong option, Please try again"<<endl;
        }
    }
}
//====//
void Run_WordXO() {
    cout << "     ---- Welcome to char tictactoe Game ----\n\n";

    while (true) {
        Player<char>* players[2];
        Word_Board<char>* B = new Word_Board<char>();
        string First_Player_Name, Second_Player_Name;

        cout << "Welcome to FCAI Word Tic-Tac-Toe Game. :)\n";

        //Player 2 setup
        cout << "Enter Player 1 name: ";
        cin >> First_Player_Name;
        cout << "Choose Player 1 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        int choice;
        cin >> choice;

        if (choice == 1) {
            players[0] = new Word_Player<char>(First_Player_Name, 'X');
            p1human= true;
        } else if (choice == 2) {
            players[0] = new Word_Random_Player<char>('X');
            p1human= false;
        } else {
            cout << "Invalid choice for Player 1. Exiting the game.\n";            delete B;
            continue;
        }
        players[0]->setBoard(B);

        // Player 2 setup
        cout << "Enter Player 2 name: ";
        cin >> Second_Player_Name;
        cout << "Choose Player 2 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;

        if (choice == 1) {
            players[1] = new Word_Player<char>(Second_Player_Name, 'O');
            p2human= true;
        } else if (choice == 2) {
            players[1] = new Word_Random_Player<char>('O');
            p2human= false;
        } else {
            cout << "Invalid choice for Player 1. Exiting the game.\n";            delete B;
            continue;
        }
        players[1]->setBoard(B);

        GameManager<char> manager(B, players);
        manager.run();

        delete B;
        delete players[0];
        delete players[1];

        cout << "\nDo you want to play again? (y/n): ";
        char Choice;
        cin >> Choice;
        if (tolower(Choice) != 'y') {
            cout << "Goodbye!\n";
            break;
        }
    }
}
//====//
void Run_NumericalXO() {
    cout << "     ---- Welcome to numerical tic-tac-toe Game ----\n\n";

    while (true) {
        Player<int>* players[2] ;
        Tictactoe* board = new Tictactoe;
        string player1Name, player2Name;

        // Reset static nums for a fresh game
        nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};

        // Player 1 setup
        cout << "Enter Player 1 name: ";
        cin >> player1Name;
        cout << "Choose Player 1 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        int choice;

        while (!(cin >> choice) || (choice != 1 && choice != 2)) {
            cout << "Invalid choice. Please enter 1 (Human) or 2 (Random Computer): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (choice == 1) {
            players[0] = new  Tictactoe_Player(player1Name, 1);
            is_p1_human=true;
        } else {
            players[0] = new  Tictactoe_RandomPlayer(1);
            is_p1_human= false;
        }
        if (!players[0]) {
            cerr << "Failed to allocate memory for Player 1. Exiting...\n";
            delete board;
            return;
        }
        players[0]->setBoard(board);

        // Player 2 setup
        cout << "Enter Player 2 name: ";
        cin >> player2Name;
        cout << "Choose Player 2 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";

        while (!(cin >> choice) || (choice != 1 && choice != 2)) {
            cout << "Invalid choice. Please enter 1 (Human) or 2 (Random Computer): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (choice == 1) {
            players[1] = new Tictactoe_Player(player2Name, 2);
            is_p2_human= true;
        } else {
            players[1] = new Tictactoe_RandomPlayer(2);
            is_p2_human = false;
        }
        if (!players[1]) {
            cerr << "Failed to allocate memory for Player 2. Exiting...\n";
            delete players[0];
            delete board;
            return;
        }
        players[1]->setBoard(board);

        // Run the game
        GameManager<int> manager(board, players);
        manager.run();

        // Clean up
        delete board;
        delete players[0];
        delete players[1];

        // Replay prompt
        cout << "\nDo you want to play again? (y/n): ";
        char replayChoice;
        cin >> replayChoice;
        if (tolower(replayChoice) != 'y') {
            cout << "Goodbye!\n";
            break;
        }
    }
}
//====//
void Run_InverseXO() {
    bool game = true;
    while(game) {
        string choice;
        Player<char>* players[2];
        auto* B = new InverseXO<char>();
        bool human1= false;
        string player_1_Name, player_2_Name;
        cout << "Enter first Player name: ";
        cin >> player_1_Name;
        while(true)
        {
            cout << "Types List:"<<endl;
            cout << "1)Human"<<endl<<"2)Random Computer"<<endl;
            cout << "Choose first Player type: ";
            cin >> choice;
            cout<<endl;
            if(choice == "1")
            {
                players[0] = new InverseX_O_Player<char>(player_1_Name, 'X');
                human1 = true;
                break;
            }
            if(choice == "2")
            {
                players[0] = new InverseX_O_Random_Player<char>('X');
                break;
            }
            cout << "Invalid choice ";
        }
        // Set up player 2
        cout << "Enter Player 2 name: ";
        cin >> player_2_Name;
        if(human1) {
            players[0] = new InverseX_O_Player<char>(player_2_Name, 'X');
            players[1] = new InverseX_O_Player<char>(player_1_Name, 'O');
        }
        while(true)
        {
            cout << "Types List:"<<endl;
            cout << "1)Human"<<endl<<"2)Random Computer"<<endl;
            cout << "Choose first Player type: ";
            cin >> choice;
            cout<<endl;
            if(choice == "1")
            {
                break;
            }
            if(choice == "2")
            {
                players[1] = new InverseX_O_Random_Player<char>('O');
                break;
            }
            cout << "Invalid choice ";
        }
        GameManager<char> x_o_game(B, players);
        x_o_game.run();
        delete B;
        for (auto & player : players) {
            delete player;
        }
        while(true) {
            cout<<"Do you want to play again ? (y/n)"<<endl;
            string answer;
            cin>>answer;
            if(answer == "y" || answer == "Y") {
                break;
            }
            if(answer == "n" || answer == "N") {
                cout<<"Thanks for playing, have a nice day <3"<<endl;
                game = false;
                break;
            }
            cout<<"Wrong option, Please try again"<<endl;
        }
    }
}
//====//
void Run_UXO() {
    bool game = true;
    while(game) {
        string choice;
        Player<char>* players[2];
        auto* B = new UltimateTicTacToeBoard<char>();
        string player_1_Name, player_2_Name;
        cout << "Enter first Player name: ";
        cin >> player_1_Name;
        while(true)
        {
            cout << "Types List:"<<endl;
            cout << "1)Human"<<endl<<"2)Random Computer"<<endl;
            cout << "Choose first Player type: ";
            cin >> choice;
            if(choice == "1")
            {
                players[0] = new UltimateXO_Player<char>(player_1_Name, 'X');
                break;
            }
            if(choice == "2")
            {
                players[0] = new UltimateRandom_Player<char>('X');
                break;
            }
            if(choice == "3") {
                cout<<"Not Ready"<<endl;
                break;
            }
            cout << "Invalid choice ";
        }

        cout << "Enter second Player name: ";
        cin >> player_2_Name;
        while(true)
        {
            cout << "Types List:"<<endl;
            cout << "1)Human"<<endl<<"2)Random Computer"<<endl;
            cout << "Choose first Player type: ";
            cin >> choice;

            if(choice == "1")
            {
                players[1] = new UltimateXO_Player<char>(player_2_Name, 'O');
                break;
            }
            if(choice == "2")
            {
                players[1] = new UltimateRandom_Player<char>('O');
                break;
            }
            if(choice == "3") {
                cout<<"Not Ready"<<endl;
                break;
            }
            cout << "Invalid choice ";
        }
        GameManager<char> x_o_game(B, players);
        x_o_game.run();
        cout<<"=============================="<<endl;
        delete B;
        for (auto & player : players) {
            delete player;
        }
        while(true) {
            cout<<"Do you want to play again ? (y/n)"<<endl;
            string answer;
            cin>>answer;
            if(answer == "y" || answer == "Y") {
                break;
            }
            if(answer == "n" || answer == "N") {
                cout<<"Thanks for playing, have a nice day <3"<<endl;
                game = false;
                break;
            }
            cout<<"Wrong option, Please try again"<<endl;
        }
    }
}
//====//
void Run_SUS(){
    bool game = true;
    while(game) {
        string choice;
        Player<char>* players[2];
        auto* B = new Sus<char>();
        string player_1_Name, player_2_Name;
        cout << "Enter first Player name: ";
        cin >> player_1_Name;
        while(true)
        {
            cout << "Types List:"<<endl;
            cout << "1)Human"<<endl<<"2)Random Computer"<<endl;
            cout << "Choose first Player type: ";
            cin >> choice;
            cout<<endl;
            if(choice == "1")
            {
                players[0] = new Sus_Player<char>(player_1_Name, 'S');
                break;
            }
            if(choice == "2")
            {
                players[0] = new Sus_RandomPlayer<char>('S');
                break;
            }
            cout << "Invalid choice ";
        }

        cout << "Enter second Player name: ";
        cin >> player_2_Name;
        while(true)
        {
            cout << "Types List:"<<endl;
            cout << "1)Human"<<endl<<"2)Random Computer"<<endl;
            cin >> choice;
            cout << "Choose first Player type: ";
            if(choice == "1")
            {
                players[1] = new Sus_Player<char>(player_2_Name, 'U');
                break;
            }
            if(choice == "2")
            {
                players[1] = new Sus_RandomPlayer<char>('U');
                break;
            }
            cout << "Invalid choice ";
        }
        GameManager<char> x_o_game(B, players);
        x_o_game.run();
        int scoreX = B->Get_P1Score();
        int scoreO = B->Get_P2score();
        cout<<"=============================="<<endl;
        if(scoreX > scoreO) {
            cout << players[0]->getname() <<" wins!\n";
        }
        else if(scoreX < scoreO) {
            cout <<players[1]->getname() <<" wins!\n";
        }
        else {
            cout<<"It's a draw!\n";
        }
        cout<<"=============================="<<endl;
        cout<<"Scores Table: " << endl <<players[0]->getname()<<" = "<<scoreX<<endl<<players[1]->getname()<<" = "<<scoreO<<"\n";
        cout<<"=============================="<<endl;
        // Clean up
        delete B;
        for (auto & player : players) {
            delete player;
        }
        while(true) {
            cout<<"Do you want to play again ? (y/n)"<<endl;
            string answer;
            cin>>answer;
            if(answer == "y" || answer == "Y") {
                break;
            }
            if(answer == "n" || answer == "N") {
                cout<<"Thanks for playing, have a nice day <3"<<endl;
                game = false;
                break;
            }
            cout<<"Wrong option, Please try again"<<endl;
        }
    }
}
//====//
