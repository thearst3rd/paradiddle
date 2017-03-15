// Class definition for Paradiddle class

#pragma once
#include <iostream>

using std::istream;
using std::ostream;

class Paradiddle
{
public:
	Paradiddle(bool);
	~Paradiddle();
	bool populateOps(istream&);
	void execute(istream& = std::cin, ostream& = std::cout);
private:
	// Command line args
	bool strict;
	struct OpNode
	{
		OpNode(int, OpNode* = NULL, OpNode* = NULL);
		~OpNode();
		int op;
		OpNode *prev;
		OpNode *next;
	};
	void addOp(int);
	// ops is the pointer to the first op in a list of ops
	OpNode *ops;
	// pc points to the current op and changes throughout
	OpNode *pc;
};

// Extra function
char readLegalChar(istream&);