#include "MemoryAnalytics.h"
#include <iostream>
#include <vector>
#include "Chessboard.h"
#include "Chessman.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Rook.h"
#include "King.h"
#include "Queen.h"
#include "Knight.h"
#include "MyChessman.h"

using namespace std;

#define MIN_OBJECT_SIZE     (2*sizeof(uint8_t*) + sizeof(ObjHeader))

void MemoryAnalytics::print_class_memory()
{
	cout << "--- --- expected --- ---" << endl;
	cout << "with VTP (+int, once per class NOT instance, Chessman size with virtual):" << endl;
	cout << "char symbol + bool white + std:.vector<Position> valid_moves + std::vector<Position> capture_moves + VTP: \n";
	cout << "sizeof(char) + sizeof(bool) + sizeof(std::vector<Position>) + sizeof(std::vector<Position>) + sizeof(int) \n";
	cout << sizeof(char) + sizeof(bool) + sizeof(std::vector<Position>*) + sizeof(std::vector<Position>*) + sizeof(int) << endl;

	cout << "without VTP (Chessman size without virtual):" << endl;
	cout << "char symbol + bool white + std:.vector<Position> valid_moves + std::vector<Position> capture_moves: \n";
	cout << "sizeof(char) + sizeof(bool) + sizeof(std::vector<Position>) + sizeof(std::vector<Position>) \n";
	cout << sizeof(char) + sizeof(bool) + sizeof(std::vector<Position>*) + sizeof(std::vector<Position>*) << endl;

	cout << "--- --- sizeof(Class) --- ---" << endl;
	cout << "bool:\t\t" << sizeof(bool) << endl;
	cout << "int:\t\t" << sizeof(int) << endl;
	cout << "vector<Position>*:\t\t" << sizeof(std::vector<Position>*) << endl;
	cout << "Chessman:\t" << sizeof(Chessman) << endl;
	cout << "Pawn:\t\t" << sizeof(Pawn) << endl;
	cout << "King:\t\t" << sizeof(King) << endl;
	cout << "Queen:\t\t" << sizeof(Queen) << endl;
	cout << "Rook:\t\t" << sizeof(Rook) << endl;
	cout << "Bishop:\t\t" << sizeof(Bishop) << endl;
	cout << "MyChessman:\t\t" << sizeof(MyChessman) << endl;

	cout << "--- --- sizeof(Instance) --- ---" << endl;
	cout << "Pawn:\t\t" << sizeof(*(new Pawn(true))) << endl;
	cout << "King:\t\t" << sizeof(*(new King(true))) << endl;
	cout << "Queen:\t\t" << sizeof(*(new Queen(true))) << endl;
	cout << "Rook:\t\t" << sizeof(*(new Rook(true))) << endl;
	cout << "Bishop:\t\t" << sizeof(*(new Bishop(true))) << endl;
	cout << "MyChessman:\t\t" << sizeof(*(new MyChessman(true))) << endl;
}
