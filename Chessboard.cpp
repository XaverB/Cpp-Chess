#include "Chessboard.h"
#include <cassert>
#include <ctype.h>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <iterator>
#include <algorithm>
#include <iostream>
#include "Chessman.h"
#include "King.h"
#include "Pawn.h"
#include "Rook.h"
#include "Queen.h"
#include "Knight.h"
#include "Bishop.h"
#include "MyChessman.h"
#include "MySecondChessman.h"
#include "Selection.h"


using namespace std;

const char SYMBOL_FILLER = '.';
const int INIT_BOARD_SIZE = 8;

/// <summary>
/// We use this board for our init. If the user increases the dimensions, we will calculate a fitting offset for the insertion algorithm.
/// </summary>
Chessman* const init_board[] = {
	new Rook{true}, new Knight{true}, new Bishop{true}, new Queen{true}, new King{true}, new Bishop{true}, new Knight{true}, new Rook{true},
	new Pawn{true}, new Pawn{true},new Pawn{true},new Pawn{true},new Pawn{true},new Pawn{true},new Pawn{true}, new Pawn{true},
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	new Pawn{false}, new Pawn{false},new Pawn{false},new Pawn{false},new Pawn{false},new Pawn{false},new Pawn{false}, new Pawn{false},
	new Rook{false}, new Knight{false}, new Bishop{false}, new Queen{false}, new King{false}, new Bishop{false}, new Knight{false}, new Rook{false} };

Chessboard::Chessboard(int size, bool use_my_chessman) : size(size), whites_turn(true), turn_counter(0)
{
	assert(size >= 8);
	assert(size % 2 == 0);
	init(use_my_chessman);
}

Chessboard::~Chessboard()
{
	cleanup();
}

void Chessboard::init(bool use_my_chessman)
{
	board = new Chessman * [size * size]{};
	Chessman* king = new King{ true };
	selection = new Selection;

	// since we use a default board with pre configured chessman
	// we need to calculate an inseriton offset if the board size is greater than the init board
	// we do not need to take care of the indexes, which exceed our init board, because they will be filled with 0x00
	int chessman_insert_offset = (size - INIT_BOARD_SIZE) / 2;

	for (int i = 0; i < INIT_BOARD_SIZE; i++) {
		for (int j = 0; j < INIT_BOARD_SIZE; j++) {
			auto man_or_nullptr = init_board[INIT_BOARD_SIZE * i + j];
			int row = i;
			int col = j + chessman_insert_offset;
			// second part of map needs double the offset so we put the chessmen at the top most bottom index
			// we don't care about possible loses due to integer div here
			if (i > INIT_BOARD_SIZE / 2)
				row += 2 * chessman_insert_offset;

			insert(row, col, man_or_nullptr);
		}
	}

	if (use_my_chessman) {
		insert_custom_chessman();
	}
}

void Chessboard::insert_custom_chessman()
{
	insert(2, size / 2 - 1, new MyChessman{ true });
	insert(size - 3, size / 2, new MyChessman{ false });

	insert(2, size / 2, new MySecondChessman{ true });
	insert(size - 3, size / 2 - 1, new MySecondChessman{ false });
}

void Chessboard::cleanup()
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++) {
			Chessman* current = at(i, j);
			if (current != nullptr)
				delete current;
		}

	delete[] board;
	delete selection;
}

Chessman* Chessboard::at(const int row, const int column) const
{
	// we only need asserts here, because all other indexing methods will use this one
	assert(row < size);
	assert(column < size);
	return board[row * size + column];
}

void Chessboard::insert(const int row, const int col, Chessman* chessman)
{
	assert(row < size);
	assert(col < size);

	board[row * size + col] = chessman;
}

void Chessboard::insert(Selection* selection) {
	insert(selection->get_row(), selection->get_col(), selection->get_chessman());
}

bool Chessboard::is_out_of_bounds(int row, int column) const
{
	if (row < 0 || column < 0) return true;
	if (row >= size || column >= size) return true;

	return false;
}

void Chessboard::clear_selection()
{
	selection->set_chessman(nullptr);;
	selection->set_position(-1, -1);
}

bool Chessboard::is_whites_turn() const
{
	return whites_turn;
}

bool Chessboard::is_game_over() const
{
	return game_over;
}

const Chessman* Chessboard::operator()(const int row, const int  col) const
{
	return at(row, col);
}

bool Chessboard::can_pass_over(const int row, const int  col) const
{
	return at(row, col) == nullptr;
}

bool Chessboard::can_land_on(const int row, const int  col, bool is_white) const
{
	Chessman* man = at(row, col);
	return
		man == nullptr ?
		true :
		man->is_white() != is_white;
}

bool Chessboard::can_capture_on(const int row, const int  col, bool is_white) const
{
	Chessman* man = at(row, col);
	return
		man == nullptr ?
		false :
		man->is_white() != is_white;
}

bool Chessboard::can_select_piece(const int row, const int  col) const
{
	if (is_out_of_bounds(row, col)) return false;
	Chessman* man = at(row, col);

	return man == nullptr ?
		false :
		is_whites_turn() == man->is_white();
}

bool Chessboard::can_move_selection_to(const int row, const int  col) const
{
	if (selection->get_chessman() == nullptr)
		return false;
	return can_move(selection->get_row(), selection->get_col(), row, col);
}

bool Chessboard::can_move_selection() const
{
	if (selection->get_chessman() == nullptr)
		return false;
	return selection->get_chessman()->can_move();
}

bool Chessboard::can_move(int from_row, int from_col, int to_row, int to_col) const
{
	Chessman* man = at(from_row, from_col);
	if (man == nullptr)
		return false;

	// we only have up to date moves from our selection
	if (man != selection->get_chessman())
		man->calculate_possible_moves(from_row, from_col, *this);

	return man->can_move(from_row, from_col, to_row, to_col, *this);
}

void Chessboard::select_piece(const int row, const int col)
{
	Chessman* man = at(row, col);
	selection->set_chessman(man);
	selection->set_position(row, col);
	if (man != nullptr)
		selection->get_chessman()->calculate_possible_moves(row, col, *this);
}

void Chessboard::move_selection_to(const int row, const int  col)
{
	// our selection moves to the square of an enemy 
	// if it is essential => game over
	// our preconditions checked, that this method can only be called on empty or enemies, so we don't need to check for friends on this field
	// we do not need to dispose the fallen warrior, because all the figures live on the stack
	set_game_over_if_essential(row, col);

	insert(selection->get_row(), selection->get_col(), nullptr);
	selection->set_position(row, col);
	insert(selection);
	change_turn();
}

void Chessboard::set_game_over_if_essential(const int row, const int col)
{
	auto man = at(row, col);
	if (man != nullptr && man->is_essential())
		game_over = true;
}

void Chessboard::change_turn()
{
	whites_turn = !whites_turn;
	turn_counter++;
}

void Chessboard::print_board() const
{
	for (int i = 0; i < size; i++) {
		printf("%3d | ", i + 1);
		for (int j = 0; j < size; j++) {
			auto man = board[i * size + j];
			char symbol = man != nullptr ? man->get_symbol() : SYMBOL_FILLER;
			// highlight selection
			if (selection->get_chessman() == man && man != nullptr) {
				printf(" (%c) ", symbol);
			}
			else {
				// seleciton can move to i, j
				if (can_move_selection_to(i, j)) {
					printf(" [%c] ", symbol);
				}
				else {
					// nothing special
					printf("%3c  ", symbol);
				}
			}
		}
		printf("\n");
		printf("    | ");
		printf("\n");
	}
}

void Chessboard::print_header() const
{
	// print current player in upper left corner
	printf("%3c  ", is_whites_turn() ? 'w' : 'b');
	for (int i = 1; i < size + 1; i++)
		printf("%3d  ", i);
	printf("\n");
	printf("%3c  ", ' ');
	for (int i = 1; i < size + 1; i++)
		printf("-----");
	printf("\n");
	printf("    | ");
	printf("\n");
}

void Chessboard::show() const
{
	print_header();
	print_board();
}