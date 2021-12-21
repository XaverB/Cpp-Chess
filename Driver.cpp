#include "Driver.h"
#include <iostream>
#include "Chessboard.h"
#include "Position.h"

using namespace std;

Driver::Driver(int size, bool use_my_chessman) : position(Position{ 0, 0 }), board(new Chessboard{ size, use_my_chessman })
{
}

Driver::~Driver()
{
	delete board;
}

void Driver::generate_new_position()
{
	position.row = rand() % board->get_size();
	position.col = rand() % board->get_size();
}


void Driver::print_start_turn()
{
	cout << "\n\n\033[1;47;35m--- --- --- --- --- NEXT TURN --- --- --- --- ---\033[0m\t\n\n" << endl;
	if (board->is_whites_turn())
		cout << "\033[3;100;30mWhite's turn!\033[0m ";
	else
		cout << "\033[3;100;30mBlack's turn!\033[0m ";

	cout << "Turn: " << board->get_turn_counter() << endl;
}

void Driver::print_game_over()
{
	if (board->is_game_over())
		cout << "\x1B[32m" << (board->is_whites_turn() ? "White" : "Black") << " won in " << board->get_turn_counter() << " turns!\033[0m\t\t" << endl;
}

void Driver::move_selection()
{
	board->move_selection_to(position.row, position.col);
	board->clear_selection();
	board->show();
}

void Driver::select_piece()
{
	bool valid_piece_selected = false;
	do
	{
		cout << "\033[3;100;30mLet's select a chessman.\033[0m " << endl;
		cout << "\tInput position.row (number between 1 and " << board->get_size() << "):" << endl;
		cin >> position.row;
		cout << "\tInput position.col (number between 1 and " << board->get_size() << "):" << endl;
		cin >> position.col;
		if (position.row > board->get_size() || position.col > board->get_size()) {
			cout << "\x1B[31mInput not in range.\033[0m\t\t" << endl;
			continue;
		}
		position.col--;
		position.row--;
		valid_piece_selected = board->can_select_piece(position.row, position.col);
		if (!valid_piece_selected) {
			cout << "\x1B[31mSelection not possible! Try again.\033[0m\t\t" << endl;
			continue;
		}

		board->select_piece(position.row, position.col);
		valid_piece_selected = board->can_move_selection();
		if (!valid_piece_selected) {
			cout << "\x1B[31mSelection not possible, because the selected piece can't move anywhere at the moment! Try again.\033[0m\t\t" << endl;
			board->clear_selection();
		}

	} while (!valid_piece_selected);
	board->show();
}

void Driver::select_destination()
{
	bool valid_destination_selected = false;
	do
	{
		cout << "\033[3;100;30mLet's select a destination.\033[0m " << endl;
		cout << "\tInput position.row (number between 1 and " << board->get_size() << "):" << endl;
		cin >> position.row;
		cout << "\tInput position.col (number between 1 and " << board->get_size() << "):" << endl;
		cin >> position.col;
		if (position.row > board->get_size() || position.col > board->get_size()) {
			cout << "\x1B[31mInput not in range.\033[0m\t\t" << endl;
			continue;
		}
		position.col--;
		position.row--;

		valid_destination_selected = board->can_move_selection_to(position.row, position.col);
		if (!valid_destination_selected)
			cout << "\x1B[31mMove not possible! Try again.\033[0m\t\t" << endl;
	} while (!valid_destination_selected);
}

void Driver::select_piece_simulation()
{
	bool valid_piece_selected = false;
	cout << "\033[3;100;30mLet's select a chessman.\033[0m " << endl;
	do
	{
		generate_new_position();

		valid_piece_selected = board->can_select_piece(position.row, position.col);
		if (!valid_piece_selected) {
			continue;
		}

		board->select_piece(position.row, position.col);
		valid_piece_selected = board->can_move_selection();
		if (!valid_piece_selected) {
			board->clear_selection();
		}

	} while (!valid_piece_selected);
	cout << "\tSelected piece at position.row (" << position.row << ") and position.col (" << position.col << ")" << endl;
	board->show();
}


void Driver::select_destination_simulation()
{
	bool valid_destination_selected = false;
	cout << "\033[3;100;30mLet's select a destination.\033[0m " << endl;
	do
	{
		generate_new_position();
		valid_destination_selected = board->can_move_selection_to(position.row, position.col);
	} while (!valid_destination_selected);
	cout << "\tSelected destination at position.row (" << position.row << ") and position.col (" << position.col << ")" << endl;
}

void Driver::start_simulation() {
	// this is our main game loop
	while (!board->is_game_over()) {

		print_start_turn();
		select_piece_simulation();
		select_destination_simulation();
		move_selection();
	}

	print_game_over();
}

void Driver::start_game()
{
	board->show();
	// this is our main game loop
	while (!board->is_game_over()) {

		print_start_turn();
		select_piece();
		select_destination();
		move_selection();
	}

	print_game_over();
}