#include "Code.hpp"
#include "Function.hpp"
#include <stdlib.h>

Code::Code(const std::string& filename):
	file_(),
	filename_(filename),
	globals_(),
	fctMap_(),
	main_("main"),
	rodata_()
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

		writeRodata();

		file()<<".text"<<std::endl
			<<".align 2"<<std::endl;

		predefinedFunctions();

		for(std::map<std::string,Function*>::iterator it = fctMap().begin(); it != fctMap().end(); ++it)
		{
			function(*(it->second));
		}

		writeMain();

		endProgram();
	}
}

void Code::predefinedFunctions()
{
	Function* fp = new Function("print");

	fp->addArg("a");
	fp->code()<<"sub sp, sp, #16"<<std::endl
		<<"str r0, [fp, #-24]"<<std::endl
		<<"mov r0, #1"<<std::endl
		<<"mov r1, #12"<<std::endl
		<<"bl calloc(PLT)"<<std::endl
		<<"mov r3, r0"<<std::endl
		<<"str r3, [fp, #-20]"<<std::endl
		<<"ldr r3, [fp, #-20]"<<std::endl
		<<"mov r2, #1"<<std::endl
		<<"str r2, [r3, #8]"<<std::endl
		<<"ldr r3, [fp, #-24]"<<std::endl
		<<"ldr r3, [r3, #8]"<<std::endl
		<<"cmp r3, #1"<<std::endl
		<<"beq .L2"<<std::endl
		<<"ldr r3, [fp, #-24]"<<std::endl
		<<"ldr r3, [r3, #8]"<<std::endl
		<<"cmp r3, #3"<<std::endl
		<<"beq .L2"<<std::endl
		<<"ldr r3, [fp, #-24]"<<std::endl
		<<"ldr r3, [r3, #8]"<<std::endl
		<<"cmp r3, #2"<<std::endl
		<<"bne .L3"<<std::endl
		<<".L2:"<<std::endl
		<<"ldr r3, [fp, #-24]"<<std::endl
		<<"ldr r3, [r3, #8]"<<std::endl
		<<"cmp r3, #1"<<std::endl
		<<"bne .L4"<<std::endl
		<<"ldr r3, [fp, #-24]"<<std::endl
		<<"ldr r2, [r3, #4]"<<std::endl
		<<"ldr r3, .L9"<<std::endl
		<<".LPIC0:"<<std::endl
		<<"add r3, pc, r3"<<std::endl
		<<"mov r0, r3"<<std::endl
		<<"mov r1, r2"<<std::endl
		<<"bl printf(PLT)"<<std::endl
		<<"str r0, [fp, #-16]"<<std::endl
		<<"b .L5"<<std::endl
		<<".L4:"<<std::endl
		<<"ldr r3, [fp, #-24]"<<std::endl
		<<"ldr r3, [r3, #0] @ float"<<std::endl
		<<"mov r0, r3"<<std::endl
		<<"bl __aeabi_f2d(PLT)"<<std::endl
		<<"mov r4, r0"<<std::endl
		<<"mov r5, r1"<<std::endl
		<<"ldr r3, .L9+4"<<std::endl
		<<".LPIC1:"<<std::endl
		<<"add r3, pc, r3"<<std::endl
		<<"mov r0, r3"<<std::endl
		<<"mov r2, r4"<<std::endl
		<<"mov r3, r5"<<std::endl
		<<"bl printf(PLT)"<<std::endl
		<<"str r0, [fp, #-16]"<<std::endl
		<<".L5:"<<std::endl
		<<"ldr r3, [fp, #-16]"<<std::endl
		<<"cmp r3, #0"<<std::endl
		<<"bge .L6"<<std::endl
		<<"mov r0, #1"<<std::endl
		<<"mov r1, #1"<<std::endl
		<<"bl calloc(PLT)"<<std::endl
		<<"mov r3, r0"<<std::endl
		<<"mov r2, r3"<<std::endl
		<<"ldr r3, [fp, #-20]"<<std::endl
		<<"str r2, [r3, #4]"<<std::endl
		<<"ldr r3, [fp, #-20]"<<std::endl
		<<"ldr r3, [r3, #4]"<<std::endl
		<<"mov r2, #0"<<std::endl
		<<"strb r2, [r3, #0]"<<std::endl
		<<"b .L8"<<std::endl
		<<".L6:"<<std::endl
		<<"mov r0, #2"<<std::endl
		<<"mov r1, #1"<<std::endl
		<<"bl calloc(PLT)"<<std::endl
		<<"mov r3, r0"<<std::endl
		<<"mov r2, r3"<<std::endl
		<<"ldr r3, [fp, #-20]"<<std::endl
		<<"str r2, [r3, #4]"<<std::endl
		<<"ldr r3, [fp, #-20]"<<std::endl
		<<"ldr r3, [r3, #4]"<<std::endl
		<<"mov r2, #49"<<std::endl
		<<"strb r2, [r3, #0]"<<std::endl
		<<"ldr r3, [fp, #-20]"<<std::endl
		<<"ldr r3, [r3, #4]"<<std::endl
		<<"add r3, r3, #1"<<std::endl
		<<"mov r2, #0"<<std::endl
		<<"strb r2, [r3, #0]"<<std::endl
		<<"b .L8"<<std::endl
		<<".L3:"<<std::endl
		<<"mov r0, #2"<<std::endl
		<<"mov r1, #1"<<std::endl
		<<"bl calloc(PLT)"<<std::endl
		<<"mov r3, r0"<<std::endl
		<<"mov r2, r3"<<std::endl
		<<"ldr r3, [fp, #-20]"<<std::endl
		<<"str r2, [r3, #4]"<<std::endl
		<<"ldr r3, [fp, #-20]"<<std::endl
		<<"ldr r3, [r3, #4]"<<std::endl
		<<"mov r2, #49"<<std::endl
		<<"strb r2, [r3, #0]"<<std::endl
		<<"ldr r3, [fp, #-20]"<<std::endl
		<<"ldr r3, [r3, #4]"<<std::endl
		<<"mov r2, #0"<<std::endl
		<<"strb r2, [r3, #0]"<<std::endl
		<<".L8:"<<std::endl
		<<"ldr r3, [fp, #-20]"<<std::endl
		<<"mov r0, r3"<<std::endl
		<<"sub sp, fp, #12"<<std::endl;

	fp->afterReturn()<<".L10:"<<std::endl
			<<".align 2"<<std::endl
			<<".L9:"<<std::endl
			<<".word .LC0-(.LPIC0+8)"<<std::endl
			<<".word .LC1-(.LPIC1+8)"<<std::endl;

	addFunction(*fp);
}

void Code::writeMain()
{
	const std::string& name = main().name();
	file()<<".global "<<name<<std::endl
		<<".type "<<name<<", %function"<<std::endl
		<<name<<":"<<std::endl
		<<"stmfd sp!, {r4, r5, r6, r7, r8, r9, r10, fp, lr}"<<std::endl //save all registers
		<<"add fp, sp, #36"<<std::endl; //set fp to point to the first stack address this function owns

	file()<<"ldr r9, =.globals"<<std::endl;

	unsigned index=0;
	for(std::list<std::string>::iterator it = globals().begin(); it != globals().end(); ++it)
	{
		file()<<"mov r0, #1"<<std::endl
			<<"mov r1, #12"<<std::endl
			<<"bl calloc(PLT)"<<std::endl
			<<"str r0, [r9, #"<<index*4<<"]"<<std::endl;

		/*float f = (float) 0;
		int* p = (int*) (&f);
		file()<<""<<std::endl*/ // initialiser à 0 les float
		index++;
	}

	file()<<main().code().str();

	file()<<"ldr r9, =.globals"<<std::endl;

	index=0;
	for(std::list<std::string>::iterator it = globals().begin(); it != globals().end(); ++it)
	{
		file()<<"str r0, [r9, #"<<index*4<<"]"<<std::endl
			<<"bl free(PLT)"<<std::endl;
		index++;
	}

	file()<<"ldmfd sp!, {r4, r5, r6, r7, r8, r9, r10, fp, pc}"<<std::endl //load back all registers and set current pc to the saved lr
		<<".size "<<name<<", .-"<<name<<std::endl;
}

void Code::function(Function& f)
{
	const std::string& name = f.name();
	file()<<".global "<<name<<std::endl
		<<".type "<<name<<", %function"<<std::endl
		<<name<<":"<<std::endl
		<<"stmfd sp!, {r4, r5, r6, r7, r8, r9, r10, fp, lr}"<<std::endl //save all registers
		<<"add fp, sp, #36"<<std::endl //set fp to point to the first stack address this function owns
		<<f.code().str()
		<<"ldmfd sp!, {r4, r5, r6, r7, r8, r9, r10, fp, pc}"<<std::endl //load back all registers and set current pc to the saved lr
		<<f.afterReturn().str()
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
		<<".file \""<<filename()<<"\""<<std::endl;
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

std::string Code::addRodata(const std::string& value)
{
	std::ostringstream o;
	o<<".ROD"<<rodata_.size();
	rodata_.push_back(value);
	return o.str();
}

std::list<std::string>& Code::rodata()
{
	return rodata_;
}


void Code::writeRodata()
{
	unsigned index=0;
	file()<<".section .rodata"<<std::endl;
	for(std::list<std::string>::iterator it = rodata().begin(); it != rodata().end(); ++it)
	{
		file()<<".align 2"<<std::endl
			<<".ROD"<<index<<":\t"<<*it<<std::endl;
		index++;
	}

	file()<<".align 2"<<std::endl
		<<".LC0: "<<std::endl
		<<".ascii \"%s\\000\""<<std::endl
		<<".global __aeabi_f2d"<<std::endl
		<<".align 2"<<std::endl
		<<".LC1: "<<std::endl
		<<".ascii \"%g\\000\""<<std::endl;
}


