#include "mazegame.h"

#include <iostream>
#include <vector>
#include <exception>

using namespace std;

int main()
{
    MazeGame myMaze; //create default map
    //set bonuses

    //print map
    system("cls");
    myMaze.printMap();
    cout << "\nPRESS SPACE TO START A GAME" << endl;
    while (_getch() != ' ');                    //press space to start a game
    bool isExit = 0;
    while (!isExit)
    {
        system("cls");
        myMaze = MazeGame();    // BAD MOVE, PLS DONT DO THIS
        myMaze.printMap();
        bool isEnd = 0;
        while (!isEnd)
        {
            /// CHECK HERE!!!!!!!!!!!!!!
            Command cmmnd = MazeGame::getMove();
            if (cmmnd == Command::BAD_COMMAND)
                continue;
            if (cmmnd == Command::STOP_GAME)
                break;

            if (myMaze.makeMove(cmmnd)) {
                system("cls");
                myMaze.printMap();
            }
            if (myMaze.isFinish())
                isEnd = 1;
        }

        cout << "\nPRESS SPACE TO RESTART OR ESC TO EXIT" << endl;
        int _choice;
        do {
            _choice = _getch();
        } while (_choice != ESC && _choice != SPACE);
        isExit = (_choice == ESC);  //press space to restart or esc to exit
    }

    system("cls");
    cout << "\nGOODBYE MY FRIEND!" << endl;
    return 0;
}
