#include "King.h"
#include <cstdlib>
#include <iostream>
#include "Chessboard.h"

// offset matrix for possible king moves
const int row_change[] = { -1, 0, 1, -1, 1, -1, 0, +1 };
// offset matrix for possible king moves
const int col_change[] = { -1, -1, -1, +0, +0, +1, +1, +1 };

King::King(bool white) : Chessman('k', white)
{

}

void King::calculate_possible_moves(const int row, const int  col, const Chessboard& cb) const
{
	valid_moves->clear();
	capture_moves->clear();

	int size = cb.get_size();
	for (int i = 0; i < size; i++) {
		int new_row = row + row_change[i];
		int new_col = col + col_change[i];
		if (cb.is_out_of_bounds(new_row, new_col))
			continue;

		auto man = cb(new_row, new_col);
		// free square
		if (man == nullptr) {
			valid_moves->push_back(Position(new_row, new_col));
		}
		// enemy on square
		else if (man->is_white() != is_white()) {
			capture_moves->push_back(Position(new_row, new_col));
		}
	}
}
