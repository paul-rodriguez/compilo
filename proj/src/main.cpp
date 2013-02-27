#include <iostream>
#include <stdexcept>
#include "Scanner.hpp"
#include "Token.hpp"
using namespace std;

int main(int argc, char** argv)
{
	if (argc == 2)
	{
		Scanner sc (argv[1]);
		try
		{
			Token t = sc.nextToken();
			while (!t.isLast())
			{
				cout << t << "\n";
				t = sc.nextToken();
			}
		}
		catch (runtime_error& error)
		{
			cerr << error.what() << endl;
		}
	}
	else
	{
		cout << "No file specified for compilation" << endl;
	}
	return 0;
}
 
