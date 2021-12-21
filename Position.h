#pragma once
struct Position
{
	int row = 0;
	int col = 0;

	Position(const int row, const int  col);
	bool operator==(const Position& p2);
	friend bool operator==(const Position& p1, const Position& p2);
};

