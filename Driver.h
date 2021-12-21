#pragma once
#include "Position.h"

class Chessboard;

class Driver
{
private:
	Chessboard* board;
	Position position;

	void print_start_turn();
	void print_game_over();
	void move_selection();
	/// <summary>
	/// Piece selection for current player
	/// </summary>
	void select_piece();
	/// <summary>
	/// Destination selection for current player
	/// select_piece must be called prior to this
	/// </summary>
	void select_destination();
	/// <summary>
	/// Used for simulation. Current bot will generate a random position for selecting pieces or selecting destination
	/// </summary>
	void generate_new_position();
	/// <summary>
	/// Bot bruteforces until it was able to select a valid piece
	/// </summary>
	void select_piece_simulation();
	/// <summary>
	/// Bot bruteforces until it was able to select a valid destination
	/// </summary>
	void select_destination_simulation();

public:
	Driver(int size = 8, bool use_my_chessman = false);
	~Driver();
	/// <summary>
	/// Start the game in two player mode
	/// </summary>
	void start_game();
	/// <summary>
	/// Start a bot game (bot vs bot),.
	/// </summary>
	void start_simulation();
};

