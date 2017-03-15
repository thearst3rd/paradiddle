// Implementation of Paradiddle class

#include <iostream>
#include <stack>
#include "Paradiddle.h"

using std::cerr;
using std::endl;
using std::stack;

/////////////////////
// OpNode Subclass //
/////////////////////

Paradiddle::OpNode::OpNode(int opN, OpNode *prevOp, OpNode *nextOp) : op(opN),
	prev(prevOp), next(nextOp) {}

Paradiddle::OpNode::~OpNode()
{
	if (next != NULL)
		delete next;
}

///////////////////////////
// Main Paradiddle Class //
///////////////////////////

Paradiddle::Paradiddle(bool s) : strict(s), ops(NULL), pc(NULL) {}

Paradiddle::~Paradiddle()
{
	if (ops != NULL)
		delete ops;
}

// Add op to the list of ops
void Paradiddle::addOp(int op)
{
	OpNode **o = &ops;
	OpNode *prev = NULL;
	while ((*o) != NULL)
	{
		prev = *o;
		o = &((*o) -> next);
	}
	*o = new OpNode(op, prev);
}

// Parse the input file and create the list of ops. Returns if successful
bool Paradiddle::populateOps(istream& input)
{
	// For strict mode
	bool expectingRight = true;
	int chainLen = -1;
	
	while (!input.eof())
	{
		// Determine the characters of pair and error check
		char c1;
		c1 = readLegalChar(input);
		if (c1 == ' ')
			break;
		
		char c2;
		c2 = readLegalChar(input);
		if (c2 == ' ')
		{
			cerr << "Found trailing " << c1 << " at EOF" << endl;
			return false;
		}
		
		if (strict && (c1 != (expectingRight ? 'R' : 'L')))
		{
			cerr << "Was expecting " << (expectingRight ? "RR or RL" :
				"LL or LR");
			cerr << ", found " << c1 << c2 << endl;
			return false;
		}
		
		// Check if they are the same and handle chain length
		bool diddle = c1 == c2;
		
		// Program should start with an RL (or LR if not strict)
		if (chainLen == -1)
		{
			if (diddle)
			{
				cerr << "Program should start with 'RL'";
				if (!strict)
					cerr << " or 'LR'";
				cerr << endl;
				return false;
			}
			
			chainLen = 0;
			continue;
		}
		
		if (diddle)
		{
			chainLen++;
			expectingRight = !expectingRight;
		}
		else
		{
			this -> addOp(chainLen);
			chainLen = 0;
		}
	}
	
	if (chainLen > 0)
		this -> addOp(chainLen);
		
	return true;
}

// Execute the stored ops (TODO, right now it actually just prints op list)
void Paradiddle::execute(istream &in, ostream &out)
{
	pc = ops;
	stack<int> mem;
	
	while (pc)
	{
		int a, b;
		switch (pc -> op)
		{
			case 1:
				pc = pc -> next;
				if (!pc)
				{
					cerr << "Attempted to push at EOF." << endl;
					return;
				}
				mem.push(pc -> op);
				break;
			case 2:
				b = mem.top();
				mem.pop();
				a = mem.top();
				mem.pop();
				
				mem.push(a + b);
				break;
			case 3:
				b = mem.top();
				mem.pop();
				a = mem.top();
				mem.pop();
				
				mem.push(a - b);
				break;
			case 4:
				b = mem.top();
				mem.pop();
				a = mem.top();
				mem.pop();
				
				mem.push(a * b);
				break;
			case 5:
				b = mem.top();
				mem.pop();
				a = mem.top();
				mem.pop();
				
				mem.push(a / b);
				break;
			case 6:
				out << mem.top();
				mem.pop();
				break;
			case 7:
				out << char(mem.top());
				mem.pop();
				break;
			case 8:
				mem.push(mem.top());
				break;
			case 9:
				mem.pop();
				break;
			default:
				break;
		}
		pc = pc -> next;
	}
}

///////////////////////////////
// Extra Non-class Functions //
///////////////////////////////

// Returns the next instance of 'R' or 'L'. Returns ' ' on EOF
char readLegalChar(istream &in)
{
	char c;
	while (!in.eof())
	{
		in >> c;
		if (c == 'R' || c == 'L')
			return c;
	}
	return ' ';
}