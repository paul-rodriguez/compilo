#include <iostream>
#include <stdexcept>
#include "Scanner.hpp"
#include "Parser.hpp"
#include "Token.hpp"
#include "CodeGenerator.hpp"
using namespace std;

int main(int argc, char** argv)
{
	if (argc == 2)
	{
		Scanner sc (argv[1]);
		try
		{
			CodeGenerator cg("code.s");
			Parser parser(sc,cg);
			parser.run();
//			Token t = sc.nextToken();
//			while (!t.isLast())
//			{
//				cout << t << "\n";
//				t = sc.nextToken();
//			}
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
	cerr.flush();
	return 0;
}
 
