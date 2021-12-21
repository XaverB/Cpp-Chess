#include "MySecondChessman.h"
#include <vector>
#include <iostream>
#include "Position.h"
#include "Chessboard.h"

// offset matrix for possible king moves
const int row_change[] = { -1, 0, 1, -1, 1, -1, 0, +1 };
// offset matrix for possible king moves
const int col_change[] = { -1, -1, -1, +0, +0, +1, +1, +1 };

const int find_valid_move_cap = 5;

MySecondChessman::MySecondChessman(bool white) : Chessman('z', white)
{
}

void MySecondChessman::calculate_possible_moves(const int row, const int col, const Chessboard& cb) const
{
	valid_moves->clear();
	capture_moves->clear();

	int change_array_size = sizeof(row_change) / sizeof(int);

	// this chessman can capture in every direction
	int size = cb.get_size();
	for (int i = 0; i < size; i++) {
		int new_row = row + row_change[i % change_array_size];
		int new_col = col + col_change[i % change_array_size];
		if (cb.is_out_of_bounds(new_row, new_col))
			continue;

		auto man = cb(new_row, new_col);
		if (man == nullptr)
			continue;
		// enemy on square
		if (man->is_white() != is_white()) {
			capture_moves->push_back(Position(new_row, new_col));
		}
	}

	// this chessman can move only in one direction if it is not a capture move
	// the movement pattern changes every turn
	
	int counter = 0;
	do
	{
		int possible_random_movement_index = rand() % change_array_size;
		int new_row = row + row_change[possible_random_movement_index];
		int new_col = col + col_change[possible_random_movement_index];
		if (!cb.is_out_of_bounds(new_row, new_col) && cb.can_land_on(new_row, new_col, is_white())) {
			valid_moves->push_back(Position(new_row, new_col));
		}
	// we try to find a move in case this valid move would be on a friendly figures position
	} while (valid_moves->size() == 0 && counter++ < find_valid_move_cap);
}
