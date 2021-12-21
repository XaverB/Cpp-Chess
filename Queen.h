#pragma once
#include "Chessman.h"
#include "Bishop.h"
#include "Rook.h"

class Queen : public Chessman, public Bishop, public Rook
{
public:
	Queen(bool white);
	virtual bool is_essential() const override { return false; }
	virtual void calculate_possible_moves(const int row, const int col, const Chessboard& cb) const override;
	virtual	std::vector<Position> get_moves() const override;
};

