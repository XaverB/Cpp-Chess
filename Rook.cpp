#include "Rook.h"
#include <vector>
#include <iostream>
#include "Chessboard.h"
#include "Position.h"



Rook::Rook(bool white) : Chessman('r', white)
{
}

void Rook::calculate_possible_moves(const int row, const int col, const Chessboard& cb) const
{
	valid_moves->clear();
	capture_moves->clear();
	
	calculate_possible_moves_all(row, col, cb);
}

void Rook::calculate_possible_moves_all(const int row, const int col, const Chessboard& cb) const
{
	calculate_possible_moves_left(row, col, cb);
	calculate_possible_moves_right(row, col, cb);
	calculate_possible_moves_up(row, col, cb);
	calculate_possible_moves_down(row, col, cb);
}

void Rook::calculate_possible_moves_down(const int row, const int col, const Chessboard& cb) const
{
	int new_row = row;
	int new_col = col;
	while (++new_row < cb.get_size())
	{
		auto man = cb(new_row, new_col);
		if (man == nullptr)
			valid_moves->push_back(Position(new_row, new_col));
		else {
			if (man->is_white() != is_white())
				capture_moves->push_back(Position(new_row, new_col));
			break;
		}
	}
}

void Rook::calculate_possible_moves_up(const int row, const int col, const Chessboard& cb) const
{
	int new_row = row;
	int new_col = col;

	while (--new_row >= 0)
	{
		auto man = cb(new_row, new_col);
		if (man == nullptr)
			valid_moves->push_back(Position(new_row, new_col));
		else {
			if (man->is_white() != is_white())
				capture_moves->push_back(Position(new_row, new_col));
			break;
		}
	}
}

void Rook::calculate_possible_moves_right(int row, int col, const Chessboard& cb) const
{
	int new_row = row;
	int new_col = col;

	while (++new_col < cb.get_size())
	{
		auto man = cb(new_row, new_col);
		if (man == nullptr)
			valid_moves->push_back(Position(new_row, new_col));
		else {
			if (man->is_white() != is_white())
				capture_moves->push_back(Position(new_row, new_col));
			break;
		}
	}
}

void Rook::calculate_possible_moves_left(int row, int col, const Chessboard& cb) const
{
	int new_row = row;
	int new_col = col;

	while (--new_col >= 0)
	{
		auto man = cb(new_row, new_col);
		if (man == nullptr)
			valid_moves->push_back(Position(new_row, new_col));
		else {
			if (man->is_white() != is_white())
				capture_moves->push_back(Position(new_row, new_col));
			break;
		}
	}
}
