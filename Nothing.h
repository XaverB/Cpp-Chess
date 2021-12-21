#pragma once
#include "Chessman.h"
class Nothing :
	public Chessman
{
public:
	Nothing();
	virtual bool is_essential() const override { return false; }
	virtual bool can_move(
		int from_row, int from_col,
		int to_row, int to_col,
		const Chessboard& cb) const override {
		return false;
	};
};

