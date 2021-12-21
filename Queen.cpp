#include "Queen.h"
#include <vector>
#include <iostream>
#include "Chessboard.h"
#include "Bishop.h"
#include "Rook.h"

using namespace std;

Queen::Queen(bool white) : Chessman('q', white), Bishop(white), Rook(white)
{
}

void Queen::calculate_possible_moves(const int row, const int  col, const Chessboard& cb) const
{
	Bishop::calculate_possible_moves(row, col, cb);
	Rook::calculate_possible_moves(row, col, cb);
}

std::vector<Position> Queen::get_moves() const
{
	int reserve_size = 0;
	vector<Position> joined_vector;

	if (Bishop::valid_moves != nullptr)
		reserve_size += Bishop::valid_moves->size();

	if (Bishop::capture_moves != nullptr)
		reserve_size += Bishop::capture_moves->size();

	if (Rook::valid_moves != nullptr)
		reserve_size += Bishop::valid_moves->size();

	if (Rook::capture_moves != nullptr)
		reserve_size += Bishop::capture_moves->size();

	joined_vector.reserve(reserve_size);
	
	if (Bishop::valid_moves != nullptr)
		joined_vector.insert(joined_vector.end(), Bishop::valid_moves->begin(), Bishop::valid_moves->end());

	if (Bishop::capture_moves != nullptr)
		joined_vector.insert(joined_vector.end(), Bishop::capture_moves->begin(), Bishop::capture_moves->end());

	if (Rook::valid_moves != nullptr)
		joined_vector.insert(joined_vector.end(), Rook::valid_moves->begin(), Rook::valid_moves->end());

	if (Rook::capture_moves != nullptr)
		joined_vector.insert(joined_vector.end(), Rook::capture_moves->begin(), Rook::capture_moves->end());
	
	return joined_vector;


}
