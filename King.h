#pragma once
#include "Chessman.h"
class King :
    public Chessman
{
public:
	King(bool white);
	virtual bool is_essential() const override { return true; }
	virtual void calculate_possible_moves(const int row, const int col, const Chessboard& cb) const override;
};

