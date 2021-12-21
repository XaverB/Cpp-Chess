#include "Bishop.h"
#include <vector>
#include <iostream>
#include "Position.h"
#include "Chessboard.h"

Bishop::Bishop(bool white) : Chessman('b', white)
{
}

void Bishop::calculate_possible_moves(const int row, const int col, const Chessboard& cb) const
{
	valid_moves->clear();
	capture_moves->clear();
	calculate_possible_moves_all(row, col, cb);

}

void Bishop::calculate_possible_moves_all(const int& row, const int& col, const Chessboard& cb) const
{
	calculate_possible_moves_top_left(row, col, cb);
	calculate_possible_moves_top_right(row, col, cb);
	calculate_possible_moves_down_left(row, col, cb);
	calculate_possible_moves_down_right(row, col, cb);
}

void Bishop::calculate_possible_moves_top_left(const int row, const int  col, const Chessboard& cb) const
{
	int new_col = col;
	int new_row = row;
	while (--new_col >= 0 && --new_row >= 0)
	{
		int retflag;
		check_square(cb, new_row, new_col, retflag);
		if (retflag == 2) break;
	}
}

void Bishop::calculate_possible_moves_top_right(const int row, const int  col, const Chessboard& cb) const
{
	int new_col = col;
	int new_row = row;
	while (++new_col < cb.get_size() && --new_row >= 0)
	{
		int retflag;
		check_square(cb, new_row, new_col, retflag);
		if (retflag == 2) break;
	}
}

void Bishop::calculate_possible_moves_down_left(const int row, const int  col, const Chessboard& cb) const
{
	int new_col = col;
	int new_row = row;
	while (--new_col >= 0 && ++new_row < cb.get_size())
	{
		int retflag;
		check_square(cb, new_row, new_col, retflag);
		if (retflag == 2) break;
	}
}

void Bishop::calculate_possible_moves_down_right(const int row, const int  col, const Chessboard& cb) const
{
	int new_col = col;
	int new_row = row;
	while (++new_col < cb.get_size() && ++new_row < cb.get_size())
	{
		int retflag;
		check_square(cb, new_row, new_col, retflag);
		if (retflag == 2) break;
	}
}

/// <summary>
/// This method is ugly, but i wanted to reduce the duplicated code in the while loops.
/// To stop the loop i need a return flag.
/// </summary>
/// <param name="cb">Chessboard</param>
/// <param name="new_row"></param>
/// <param name="new_col"></param>
/// <param name="retflag">2 if we should break the callers loop</param>
void Bishop::check_square(const Chessboard& cb, int new_row, int new_col, int& retflag) const
{
	retflag = 1;
	auto man = cb(new_row, new_col);
	if (man == nullptr)
		valid_moves->push_back(Position(new_row, new_col));
	else {
		if (man->is_white() != is_white())
			capture_moves->push_back(Position(new_row, new_col));
		{ retflag = 2; return; };
	}
}
