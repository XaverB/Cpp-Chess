#pragma once
class Move
{
	int ;
	int length;
	void Move();
	void ~Move();

public:
	void add(int row, int col);
	void get(int index);
	bool is_empty() const { return length == 0; }
};

