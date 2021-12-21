#include "Pawn.h"
#include <cstdlib>
#include <iostream>
#include "Chessboard.h"

Pawn::Pawn(bool white) : Chessman('p', white)
{
}

void Pawn::calculate_possible_moves(const int row, const int  col, const Chessboard& cb) const
{
	valid_moves->clear();
	capture_moves->clear();
	
	// white starts top
	int new_row = is_white() ? (row+1) : (row-1);
	bool out_of_bounds = cb.is_out_of_bounds(new_row, col);
	if (out_of_bounds)
		return;

	add_to_valid_moves_if_empty(cb, new_row, col);
	calculate_possible_takes(col, cb, new_row);
}

void Pawn::add_to_valid_moves_if_empty(const Chessboard& cb, const int row, const int  col) const
{
	if (cb(row, col) == nullptr)
		valid_moves->push_back(Position(row, col));
}

void Pawn::calculate_possible_takes(int col, const Chessboard& cb, int row) const
{
	if (col - 1 >= 0) {
		auto man = cb(row, col - 1);
		add_to_capture_moves_if_enemy(man, row, col-1);
	}
	if (col + 1 <= 7) {
		auto man = cb(row, col + 1);
		add_to_capture_moves_if_enemy(man, row, col+1);
	}
}

void Pawn::add_to_capture_moves_if_enemy(const Chessman* man, const int row, const int  col) const
{
	if (man != nullptr && man->is_white() != is_white())
		capture_moves->push_back(Position(row, col));
}
