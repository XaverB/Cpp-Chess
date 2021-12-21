#pragma once
#include "Chessman.h"
class Rook :
    public Chessman
{
private:
	void calculate_possible_moves_down(const int row, const int col, const Chessboard& cb) const;
	void calculate_possible_moves_up(const int row, const int col, const Chessboard& cb) const;
	void calculate_possible_moves_right(int row, int col, const Chessboard& cb) const;
	void calculate_possible_moves_left(int row, int col, const Chessboard& cb) const;
	void calculate_possible_moves_all(const int row, const int col, const Chessboard& cb) const;

public:
	Rook(bool white);
	virtual bool is_essential() const override { return false; }
	virtual void calculate_possible_moves(const int row, const int col, const Chessboard& cb) const override;
};

