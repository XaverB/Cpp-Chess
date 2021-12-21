#include "Selection.h"

Selection::Selection()
{
	chessman = nullptr;
	row = -1;
	col = -1;
}

Selection::Selection(Chessman* chessman, const int row, const int  col) : chessman(chessman), row(row), col(col)
{
}

void Selection::set_chessman(Chessman* chessman)
{
	this->chessman = chessman;
}

Chessman* Selection::get_chessman() const
{
	return chessman;
}

void Selection::set_position(const int row, const int  col)
{
	this->row = row;
	this->col = col;
}

int Selection::get_row() const
{
	return row;
}

int Selection::get_col() const
{
	return col;
}
