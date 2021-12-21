#pragma once
#include "Chessman.h"
class MySecondChessman :
	public Chessman
{
public:
	MySecondChessman(bool white);
	virtual bool is_essential() const override { return false; }
	virtual void calculate_possible_moves(const int row, const int col, const Chessboard& cb) const override;
};

