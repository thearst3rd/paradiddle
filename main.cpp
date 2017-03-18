// Paradiddle Esoteric Language implementation in C++
// Language and Implementation by Terry Hearst

#include <iostream>
#include <fstream>
#include <cstring>
#include "Paradiddle.h"

using std::cout;
using std::endl;
using std::cerr;
using std::ifstream;
using std::ostream;

int main(int argc, char *argv[])
{
	// Show program usage
	if (argc < 2 || strcmp(argv[1], "help") == 0 || strcmp(argv[1], "/?") == 0)
	{
		cout << "Usage:" << endl;
		cout << argv[0] << " <input file>" << endl;
		return 0;
	}
	
	// Set default parameters
	bool strict = false;
	
	// Process extra command line args
	for (int i = 2; i < argc; i++)
	{
		if (strcmp(argv[i], "-strict") == 0)
		{
			strict = true;
		}
		else
		{
			cerr << "Unknown command line arg '" << argv[i] << '\'' << endl;
		}
	}
	
	Paradiddle p(strict);
	
	ifstream input;
	input.open(argv[1]);
	if (input.fail())
	{
		cerr << "Error opening input file '" << argv[1] << '\'' << endl;
		return 1;
	}
	
	bool success = p.populateOps(input);
	input.close();
	
	if (!success)
		return -1;
	
	p.execute();
	
	return 0;
}