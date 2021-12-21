#pragma once
#include "Chessman.h"
class Pawn :
    public Chessman
{
private:
	void calculate_possible_takes(int col, const Chessboard& cb, int row) const;
	void add_to_capture_moves_if_enemy(const Chessman* man, const int row, const int  col) const;
	void add_to_valid_moves_if_empty(const Chessboard& cb, const int row, const int  col) const;

	public:
		Pawn(bool white);
		virtual bool is_essential() const override { return false; }
		virtual void calculate_possible_moves(const int row, const int col, const Chessboard& cb) const override;

		
		
};

