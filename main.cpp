#include "main.h"
#include <iostream>
#include <algorithm>
#include "Driver.h"
#include "MemoryAnalytics.h"

using namespace std;

/// <summary>
/// Returns a command line parameter as char*
/// </summary>
char* get_cmd_options(char** begin, char** end, const std::string& option)
{
	char** itr = std::find(begin, end, option);
	if (itr != end && ++itr != end)
	{
		return *itr;
	}
	return 0;
}

/// <summary>
/// Check if command line parameter with prefix exists
/// </summary>
bool cmd_option_exists(char** begin, char** end, const std::string& option)
{
	return std::find(begin, end, option) != end;
}

void print_welcome()
{
	cerr << "--- --- --- Simple C++ chess --- --- ---" << endl;
	cerr << "USAGE: no arguments for chess game" << endl;
	cerr << "USAGE: -b for bot game" << endl;
	cerr << "USAGE: -m for memory analytics about classes" << endl;
	cerr << "USAGE: -s <INT> to change board size. default size 8, must be > 8 and straight" << endl;
	cerr << "USAGE: -a to play with the super cool MyChessman figures." << endl;
	cerr << "--- --- ---     Have Fun     --- --- ---" << endl;
}

int main(int argc, char** argv) {
	srand(time(NULL));

	int size = 8;
	bool use_my_chessman = false;
	print_welcome();

	// custom size parameter
	if (cmd_option_exists(argv, argv + argc, "-s"))
	{
		char* c_size = get_cmd_options(argv, argv + argc, "-s");
		size = atoi(c_size);
		cout << "Found size parameter. Initialising board with size " << size << endl;
	}
	// use my custom chessman
	if (cmd_option_exists(argv, argv + argc, "-a"))
	{
		use_my_chessman = true;
	}
	// start a bot game
	if (cmd_option_exists(argv, argv + argc, "-b"))
	{
		cout << "Found bot parameter. Launching bot game" << endl;
		Driver driver{ size, use_my_chessman };
		driver.start_simulation();
	}
	// start memory analytics output
	else if (cmd_option_exists(argv, argv + argc, "-m"))
	{
		cout << "Found memory parameter. Launching memory analytics " << endl;
		MemoryAnalytics analytics;
		analytics.print_class_memory();
	}
	// start player vs player game
	else {
		Driver driver{ size, use_my_chessman };
		driver.start_game();
	}


	return 0;
}

