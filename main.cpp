#include <iostream>
#include <conio.h>
#include <vector>
#include <exception>
#include "mazegame.h"

using namespace std;

struct Position
{
    int col;
    int row;
};

bool operator==(const Position& lhs, const Position& rhs)
{
    return (lhs.col == rhs.col) && (lhs.row == rhs.col);
}

const char ESC = 27;
const char SPACE = ' ';
const unsigned char PLAYER_SYMBOL = 254;
const unsigned char FINISH_SYMBOL = 0;
const int def_cols_count = 10;
const int def_rows_count = 10;
const Position def_start_coord {1, 0};
const Position def_end_coord {10, 11};

enum class Command { MOVE_LEFT, MOVE_DOWN, MOVE_RIGHT, MOVE_UP, STOP_GAME, BAD_COMMAND };



Command getMove()
{
    int c = 0;
    c = _getch();
    switch (c)
    {
        case 'd': return Command::MOVE_LEFT;
        case 's': return Command::MOVE_DOWN;
        case 'a': return Command::MOVE_RIGHT;
        case 'w': return Command::MOVE_UP;
        case ESC: return Command::STOP_GAME;
        default : return Command::BAD_COMMAND;
    }
}

class Maze
{
public:
    Maze() : _cols_count(def_cols_count),
             _rows_count(def_rows_count),
             _player_coord(def_start_coord),
             _finish(def_end_coord),
             map(_cols_count + 2, vector <unsigned char>(_rows_count + 2))
    {
        _makeBorders();
    }

    Maze(size_t columns_count, size_t rows_count, const Position& start_pos, const Position& end_pos) :
             _cols_count(columns_count),
             _rows_count(rows_count),
             _player_coord(start_pos),
             _finish(end_pos),
             map(_cols_count + 2, vector <unsigned char>(_rows_count + 2))
    {
        _makeBorders();
    }

    void printMap() const
    {
        for (const auto& column : map)
        {
            for (const auto& row : column)
            {
                cout << row;
            }
            cout << endl;
        }
    }

    bool makeMove(const Command& new_move)
    {
        bool isMoved = 0;
        switch (new_move)
        {
        case Command::MOVE_LEFT :
        {
            if (_isMovable({_player_coord.col, _player_coord.row + 1}))
            {
                map[size_t(_player_coord.col)][size_t(_player_coord.row)] = 0;
                ++_player_coord.row;
                map[size_t(_player_coord.col)][size_t(_player_coord.row)] = PLAYER_SYMBOL;
                isMoved = 1;
            }
            break;
        }
        case Command::MOVE_DOWN :
        {
            if (_isMovable({_player_coord.col + 1, _player_coord.row}))
            {
                map[size_t(_player_coord.col)][size_t(_player_coord.row)] = 0;
                ++_player_coord.col;
                map[size_t(_player_coord.col)][size_t(_player_coord.row)] = PLAYER_SYMBOL;
                isMoved = 1;
            }
            break;
        }
        case Command::MOVE_RIGHT :
        {
            if (_isMovable({_player_coord.col, _player_coord.row - 1}))
            {
                map[size_t(_player_coord.col)][size_t(_player_coord.row)] = 0;
                --_player_coord.row;
                map[size_t(_player_coord.col)][size_t(_player_coord.row)] = PLAYER_SYMBOL;
                isMoved = 1;
            }
            break;
        }
        case Command::MOVE_UP :
        {
            if (_isMovable({_player_coord.col - 1, _player_coord.row}))
            {
                map[size_t(_player_coord.col)][size_t(_player_coord.row)] = 0;
                --_player_coord.col;
                map[size_t(_player_coord.col)][size_t(_player_coord.row)] = PLAYER_SYMBOL;
                isMoved = 1;
            }
            break;
        }
        default:
        {
            throw runtime_error("BAD MOVE PASSED TO makeMove()");
        }
        }
        return isMoved;
    }

    bool isFinish() const
    {
        return _player_coord == _finish;
    }

private:
    size_t _cols_count, _rows_count;
    Position _player_coord, _finish;
    vector <vector <unsigned char> > map;

    void _makeBorders()
    {
        for (auto& i : map.front())
            i = 205;
        for (auto& i : map.back())
            i = 205;
        for (auto& rows : map) {
            rows.front() = 186;
            rows.back() = 186;
        }
        map.front().front() = 201;
        map.front().back()  = 187;
        map.back().front() = 200;
        map.back().back() = 188;

        map.at(size_t(_player_coord.col)).at(size_t(_player_coord.row)) = PLAYER_SYMBOL;
        map.at(size_t(_finish.col)).at(size_t(_finish.row)) = FINISH_SYMBOL;
    }

    bool _isMovable(const Position& pos) const
    {
        if (!_isBorder(pos))
            return map.at(size_t(pos.col)).at(size_t(pos.row)) == 0;
        return false;
    }

    bool _isBorder(const Position& pos) const
    {
        if (pos.col < 0 || pos.row < 0)
            return true;
        if (size_t(pos.col) >= map.size())
            return true;
        if (size_t(pos.row) >= map.at(size_t(pos.col)).size())
            return true;
        return false;
    }

};


int main()
{
    Maze myMaze; //create default map
    //set bonuses

    //print map
    do {
        system("cls");
        myMaze.printMap();
        cout << "\nPRESS SPACE TO START A GAME" << endl;
    } while (_getch() != ' '); //press space to start a game
    bool isExit = 0;
    while (!isExit)
    {
        system("cls");
        myMaze.printMap();
        bool isEnd = 0;
        while (!isEnd)
        {
            /// CHECK HERE!!!!!!!!!!!!!!
            Command cmmnd = getMove();
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
