#include "mazegame.h"

bool operator==(const Position& lhs, const Position& rhs)
{
    return (lhs.col == rhs.col) && (lhs.row == rhs.row);
}

MazeGame::MazeGame() : _cols_count(def_cols_count),
         _rows_count(def_rows_count),
         _player_coord(def_start_coord),
         _finish(def_end_coord),
         map(_cols_count + 2, std::vector <unsigned char>(_rows_count + 2))
{
    _makeBorders();
}

MazeGame::MazeGame(size_t columns_count, size_t rows_count, const Position& start_pos, const Position& end_pos) :
         _cols_count(columns_count),
         _rows_count(rows_count),
         _player_coord(start_pos),
         _finish(end_pos),
         map(_cols_count + 2, std::vector <unsigned char>(_rows_count + 2))
{
    _makeBorders();
}

void MazeGame::printMap() const
{
    for (const auto& column : map)
    {
        for (const auto& row : column)
        {
            std::cout << row;
        }
        std::cout << std::endl;
    }
}

bool MazeGame::makeMove(const Command& new_move)
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
        throw std::runtime_error("BAD MOVE PASSED TO makeMove()");
    }
    }
    return isMoved;
}

bool MazeGame::isFinish() const
{
    return _player_coord == _finish;
}

void MazeGame::_makeBorders()
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

bool MazeGame::_isMovable(const Position& pos) const
{
    if (!_isBorder(pos))
        return map.at(size_t(pos.col)).at(size_t(pos.row)) == 0;
    return false;
}

bool MazeGame::_isBorder(const Position& pos) const
{
    if (pos.col < 0 || pos.row < 0)
        return true;
    if (size_t(pos.col) >= map.size())
        return true;
    if (size_t(pos.row) >= map.at(size_t(pos.col)).size())
        return true;
    return false;
}

Command MazeGame::getMove()
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
