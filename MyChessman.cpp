#include "MyChessman.h"
#include <vector>
#include <iostream>
#include "Position.h"
#include "Chessboard.h"

// offset matrix for possible moves
const int row_change[] = { 1, 2, -1, -2, 0, 0, 0, 0 };
// offset matrix for possible moves
const int col_change[] = { 0, 0, 0, 0, 1, 2, -1, -2 };

MyChessman::MyChessman(bool white) : Chessman('x', white)
{
}

void MyChessman::calculate_possible_moves(const int row, const int col, const Chessboard& cb) const
{
	valid_moves->clear();
	capture_moves->clear();

	int change_array_size = sizeof(row_change) / sizeof(int);

	int size = cb.get_size();
	for (int i = 0; i < size; i++) {
		int new_row = row + row_change[i % change_array_size];
		int new_col = col + col_change[i % change_array_size];
		if (cb.is_out_of_bounds(new_row, new_col))
			continue;

		// free square
		if (cb.can_pass_over(new_row, new_col)) {
			valid_moves->push_back(Position(new_row, new_col));
		}
		// enemy on square
		else if (cb.can_capture_on(new_row, new_col, is_white())) {
			capture_moves->push_back(Position(new_row, new_col));
		}
	}
}
