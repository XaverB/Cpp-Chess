#pragma once
#include <vector>
#include <string>
#include "Position.h"

// forward declaration so we can use the class Chessboard in this header
class Chessboard;

class Chessman {
private:
	char symbol;
	bool white;

protected:
	/// <summary>
	/// Vector with all valid moves exclusive capture_moves.
	/// Computed with method calculate_possible_moves
	/// </summary>
	std::vector<Position>* valid_moves;
	/// <summary>
	/// Vector with all capture moves.
	/// Computed with method calculate_possible_moves
	/// </summary>
	std::vector<Position>* capture_moves;

public:
	Chessman(char symbol, bool is_white);
	virtual ~Chessman();
	char get_symbol() const;
	char get_color() const { return is_white() ? 'w' : 'b'; };
	bool is_white() const { return white; };
	virtual bool is_essential() const { return false; }
	/// <summary>
	/// Check if we can move from_row, from_col to to_row, to_col.
	/// calculate_possible_moves must be called prior to this method.
	/// </summary>
	bool can_move(
		int from_row, int from_col,
		int to_row, int to_col,
		const Chessboard& cb) const;
	/// <summary>
	/// Returns all valid moves (valid_moves + capture_moves)
	/// </summary>
	virtual	std::vector<Position> get_moves() const;
	/// <summary>
	/// Calculate all possible moves (valid_moves, capture_moves)
	/// </summary>
	virtual void calculate_possible_moves(const int row, const int col, const Chessboard& cb) const = 0;
	/// <summary>
	/// Check if this chessman is possible to move.
	/// </summary>
	/// <returns></returns>
	bool can_move() const;
};


