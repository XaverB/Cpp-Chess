#pragma once

class Chessman;

class Selection
{
	int row;
	int col;
	Chessman* chessman;

public:
	Selection();
	Selection(Chessman* chessman, const int row, const int  col);
	void set_chessman(Chessman* chessman);
	Chessman* get_chessman() const;
	void set_position(const int row, const int  col);
	int get_row() const;
	int get_col() const;
};

