#pragma once

#include <vector>

// forward declaration so we can use these classes in this header
class Chessman;
class Selection;

class Chessboard{
private:
	/// <summary>
	/// Size of board (size * size)
	/// Minimum 8
	/// Must be a even number
	/// </summary>
	int size;
	/// <summary>
	/// State which player's turn is the current one
	/// </summary>
	bool whites_turn;
	/// <summary>
	/// State if it is game over
	/// </summary>
	bool game_over;
	/// <summary>
	/// Counter for turns
	/// </summary>
	int turn_counter;
	/// <summary>
	/// Current Selection (Pointer to selected chessman and position)
	/// </summary>
	Selection* selection;
	/// <summary>
	/// The board.
	/// Array with pointers to chessman or nullptr if empty field
	/// </summary>
	Chessman** board;
	/// <summary>
	/// Initialize the board.
	/// </summary>
	/// <param name="use_my_chessman">Include my own creation in this board</param>
	void init(bool use_my_chessman);
	/// <summary>
	/// Inserts my custom chessman MyChessman into the board
	/// </summary>
	void insert_custom_chessman();
	/// <summary>
	/// Dispose the board
	/// </summary>
	void cleanup();
	/// <summary>
	/// Return chessman at row, column or nullptr if empty
	/// </summary>
	/// <param name="row">Row</param>
	/// <param name="column">Column</param>
	/// <returns>Chessman* or nullptr</returns>
	Chessman* at(const int row, const int column) const;
	/// <summary>
	/// Inserts a chessman in the board at row, column
	/// </summary>
	/// <param name="row">Row</param>
	/// <param name="column">Col</param>
	/// <param name="chessman">Pointer to chessman</param>
	void insert(const int row, const int column, Chessman* chessman);
	/// <summary>
	/// Inserts a chessman in the selection at the selections.position row, col
	/// </summary>
	/// <param name="selection">Selection to insert in the board</param>
	void insert(Selection* selection);
	/// <summary>
	/// Changes the current player and moves to the next turn.
	/// </summary>
	void change_turn();
	/// <summary>
	/// Print the boards header at cout
	/// </summary>
	void print_header() const;
	/// <summary>
	/// Prints the board and its contents at cout
	/// </summary>
	void print_board() const;
	/// <summary>
	/// Check if the figure at row, col is essential and set game_over = true if condition is met.
	/// </summary>
	/// <param name="row"></param>
	/// <param name="col"></param>
	void set_game_over_if_essential(const int row, const int col);
public:
 /// <summary>
 /// Constructor
 /// </summary>
 /// <param name="size">Size of board (size*size). Minimum 8, must be an even number</param>
 /// <param name="use_my_chessman">Use my custom chessman MyChessman</param>
 Chessboard(int size = 8, bool use_my_chessman = false);
 /// <summary>
 /// Destructor
 /// </summary>
 ~Chessboard();
 /// <summary>
 /// State which player's turn is the current one
 /// </summary>
 bool is_whites_turn() const;
 /// <summary>
 /// State if game is over
 /// </summary>
 bool is_game_over() const;
 /// <summary>
 /// Get board size
 /// </summary>
 int get_size() const { return size; } 
 /// <summary>
 /// Get chessman at row, col
 /// </summary>
 const Chessman* operator() (const int row, const int col) const;
 /// <summary>
 /// Check if the field is empty, so any figure can pass over
 /// </summary>
 bool can_pass_over(const int row, const int  col) const;
 /// <summary>
 /// Check if is_white can land on this field. 
 /// </summary>
 bool can_land_on(const int row, const int  col, bool is_white) const;
 /// <summary>
 /// Check if we can capture a figure on this field with respect to is_white.
 /// </summary>
 bool can_capture_on(const int row, const int  col, bool is_white) const;
 /// <summary>
 /// Check if the current player can select at row, col
 /// </summary>
 bool can_select_piece(const int row, const int  col) const;
 /// <summary>
 /// Check if the current player can move it's selection to row, col
 /// </summary>
 bool can_move_selection_to(const int row, const int  col) const;
 /// <summary>
 /// Check if the selection got any valid moves
 /// </summary>
 bool can_move_selection() const;
 /// <summary>
 /// Check if we can move from_row, from_col to to_row, to_col
 /// </summary>
 bool can_move(int from_row, int from_col, int to_row, int to_col) const;
 /// <summary>
 /// Select piece at row, col
 /// </summary>
 void select_piece(const int row, const int  col);
 /// <summary>
 /// Moves the players current selection to row, col
 /// </summary>
 void move_selection_to(const int row, const int  col);
 /// <summary>
 /// Get the current turn counters value
 /// </summary>
 /// <returns></returns>
 int get_turn_counter() const { return turn_counter; }
 /// <summary>
 /// Check if the passed row, col is out of boards boundaries
 /// </summary>
 bool is_out_of_bounds(const int row, const int col) const;
 /// <summary>
 /// Clears the current players selection
 /// </summary>
 void clear_selection();
 /// <summary>
 /// Prints the board in cout
 /// </summary>
 void show() const;
};