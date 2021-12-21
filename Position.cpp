#include "Position.h"

Position::Position(const int row, const int  col) : row(row), col(col)
{
}

bool Position::operator==(const Position& p2)
{
	return this->col == p2.col && this->row == p2.row;
}

bool operator==(const Position& p1, const Position& p2)
{
	return p1 == p2;
}
