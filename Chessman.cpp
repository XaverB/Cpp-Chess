#include "Chessman.h"
#include <ctype.h>
#include <vector>
#include "Position.h"
#include "Chessboard.h"
#include <string>

using namespace std;

Chessman::Chessman(char symbol, bool white) : symbol(symbol), white(white)
{
	valid_moves = new vector<Position>;
	capture_moves= new vector<Position>;
}

Chessman::~Chessman()
{
	valid_moves->clear();
	capture_moves->clear();

	delete valid_moves;
	delete capture_moves;
}

char Chessman::get_symbol() const
{
	return is_white() ? toupper(symbol) : tolower(symbol); 
}

bool Chessman::can_move(int from_row, int from_col, int to_row, int to_col, const Chessboard& cb) const
{
	auto moves = get_moves();
	auto it_moves = std::find(
		moves.begin(),
		moves.end(),
		Position(to_row, to_col));
	if (it_moves != moves.end())
		return true;

	return false;
}

std::vector<Position> Chessman::get_moves() const
{
	vector<Position> joined_vector;

	if (valid_moves == nullptr || capture_moves == nullptr)
		return joined_vector;
	
	joined_vector.reserve(valid_moves->size() + capture_moves->size());
	joined_vector.insert(joined_vector.end(), valid_moves->begin(), valid_moves->end());
	joined_vector.insert(joined_vector.end(), capture_moves->begin(), capture_moves->end());
	return joined_vector;
}

bool Chessman::can_move() const
{
	return get_moves().size() > 0;

	if (valid_moves == nullptr || capture_moves == nullptr)
		return false;

	return valid_moves->size() > 0 || capture_moves->size() > 0;
}
