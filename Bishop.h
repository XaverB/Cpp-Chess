#pragma once
#include "Chessman.h"
class Bishop :
    public Chessman
{

private:
	void calculate_possible_moves_top_left(int new_col, int new_row, const Chessboard& cb) const;
	void calculate_possible_moves_top_right(int new_col, int new_row, const Chessboard& cb) const;
	void calculate_possible_moves_down_left(int new_col, int new_row, const Chessboard& cb) const;
	void calculate_possible_moves_down_right(int new_col, int new_row, const Chessboard& cb) const;
	void calculate_possible_moves_all(const int& row, const int& col, const Chessboard& cb) const;

public:
	Bishop(bool white);
	virtual bool is_essential() const override { return false; }
	virtual void calculate_possible_moves(const int row, const  int col, const Chessboard& cb) const override;
	void check_square(const Chessboard& cb, int new_row, int new_col, int& retflag) const;
};

