#include "Code.hpp"
#include "Function.hpp"
#include <stdlib.h>

Code::Code(const std::string& filename):
	file_(),
	filename_(filename),
	globals_(),
	fctMap_(),
	main_("main")
{
	file().open(filename.c_str());
}

Code::~Code()
{
	for(std::map<std::string,Function*>::iterator it = fctMap().begin(); it != fctMap().end(); ++it)
	{
		delete (it->second);
	}
}

void Code::write()
{
	if(programHeader_)
	{
		programHeader();

		for(std::list<std::string>::iterator it = globals().begin(); it != globals().end(); ++it)
		{
			file()<<".comm "<<*it<<",4"<<std::endl;
		}

		file()<<".data"<<std::endl
			<<".globals:"<<std::endl;

		for(std::list<std::string>::iterator it = globals().begin(); it != globals().end(); ++it)
		{
			file()<<".word "<<*it<<std::endl;
		}
		file()<<".text"<<std::endl
			<<".align"<<std::endl;

		for(std::map<std::string,Function*>::iterator it = fctMap().begin(); it != fctMap().end(); ++it)
		{
			function(*(it->second));
		}

		writeMain();

		endProgram();
	}
}

void Code::writeMain()
{
	const std::string& name = main().name();
	file()<<".global "<<name<<std::endl
		<<".type "<<name<<", %function"<<std::endl
		<<name<<":"<<std::endl
		<<"stmfd sp!, {r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, fp, lr}"<<std::endl //save all registers
		<<"add fp, sp, #48"<<std::endl; //set fp to point to the first stack address this function owns

	unsigned index=0;
	for(std::list<std::string>::iterator it = globals().begin(); it != globals().end(); ++it)
	{
		file()<<"mov r0, #1"<<std::endl
			<<"mov r1, #12"<<std::endl
			<<"bl calloc(PLT)"<<std::endl
			<<"str r0, .globals+"<<index*4<<std::endl;

		/*float f = (float) 0;
		int* p = (int*) (&f);
		file()<<""<<std::endl*/ // initialiser à 0 les float
		index++;
	}

	file()<<main().code().str();

	index=0;
	for(std::list<std::string>::iterator it = globals().begin(); it != globals().end(); ++it)
	{
		file()<<"ldr r0, .globals+"<<index*4<<std::endl
			<<"bl free(PLT)"<<std::endl;
		index++;
	}

	file()<<"ldmfd sp!, {r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, fp, pc}"<<std::endl //load back all registers and set current pc to the saved lr
		<<".size "<<name<<", .-"<<name<<std::endl;
}

void Code::function(Function& f)
{
	const std::string& name = f.name();
	file()<<".global "<<name<<std::endl
		<<".type "<<name<<", %function"<<std::endl
		<<name<<":"<<std::endl
		<<"stmfd sp!, {r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, fp, lr}"<<std::endl //save all registers
		<<"add fp, sp, #48"<<std::endl //set fp to point to the first stack address this function owns
		<<f.code().str()
		<<"ldmfd sp!, {r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, fp, pc}"<<std::endl //load back all registers and set current pc to the saved lr
		<<".size "<<name<<", .-"<<name<<std::endl;
}

void Code::programHeader()
{
	file()<<".arch armv5te"<<std::endl
		<<".fpu softvfp"<<std::endl
		<<".eabi_attribute 20, 1"<<std::endl
		<<".eabi_attribute 21, 1"<<std::endl
		<<".eabi_attribute 23, 3"<<std::endl
		<<".eabi_attribute 24, 1"<<std::endl
		<<".eabi_attribute 25, 1"<<std::endl
		<<".eabi_attribute 26, 2"<<std::endl
		<<".eabi_attribute 30, 6"<<std::endl
		<<".eabi_attribute 18, 4"<<std::endl
		<<".file "<<filename()<<std::endl<<std::endl;
}

bool Code::isGlobal(const std::string& name) const
{
	bool found = false;
	std::list<std::string>::const_iterator it = globals().begin();
	while(!found && it != globals().end())
	{
		if(name.compare(*it) == 0)
		{
			found = true;
		}
		else
		{
			++it;
		}
	}
	return found;
}

void Code::endProgram()
{
	 file()<<".ident \"Potato Compiler\""<<std::endl
		<<".section .note.GNU-stack,\"\",%progbits"<<std::endl;
}

std::list<std::string>& Code::globals() { return globals_; }
const std::list<std::string>& Code::globals() const { return globals_; }
std::map<std::string,Function*>& Code::fctMap() { return fctMap_; }
Function& Code::fct(const std::string& name) { return *(fctMap()[name]); }

std::ofstream& Code::file() { return file_; }
const std::string& Code::filename() { return filename_; }

void Code::setProgramHeader(bool programHeader)
{
	programHeader_ = programHeader;
}

void Code::addGlobal(const std::string& name)
{
	globals().push_back(name);
}

void Code::addFunction(Function& f)
{
	fctMap()[f.name()] = &f;
}

unsigned Code::globalOffset(const std::string& name) const
{
	unsigned index = 0;
	bool found = false;
	std::list<std::string>::const_iterator it = globals().begin();
	while(!found && it != globals().end())
	{
		if(name.compare(*it) == 0)
		{
			found = true;
		}
		else
		{
			++it;
			++index;
		}
	}
	return 4*index;
}

Function& Code::main() { return main_; }


