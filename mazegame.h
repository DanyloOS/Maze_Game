#ifndef MAZEGAME_H
#define MAZEGAME_H

#include <vector>
#include <iostream>
#include <conio.h>
#include <exception>

enum class Command { MOVE_LEFT,
                     MOVE_DOWN,
                     MOVE_RIGHT,
                     MOVE_UP,
                     STOP_GAME,
                     BAD_COMMAND };

struct Position
{
    int col;
    int row;
};

bool operator==(const Position& lhs, const Position& rhs);

const char ESC = 27;
const char SPACE = ' ';
const unsigned char PLAYER_SYMBOL = 254;
const unsigned char FINISH_SYMBOL = 0;
const int def_cols_count = 10;
const int def_rows_count = 10;
const Position def_start_coord {1, 0};
const Position def_end_coord {10, 11};

class MazeGame
{
public:
    MazeGame();
    MazeGame(size_t columns_count,
         size_t rows_count,
         const Position& start_pos,
         const Position& end_pos);

    static Command getMove();
    void printMap() const;
    bool makeMove(const Command& new_move);
    bool isFinish() const;

private:
    size_t _cols_count, _rows_count;
    Position _player_coord, _finish;
    std::vector <std::vector <unsigned char> > map;

    void _makeBorders();
    bool _isMovable(const Position& pos) const;
    bool _isBorder(const Position& pos) const;
};

#endif // MAZEGAME_H
