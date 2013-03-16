#include "CodeGenerator.hpp"
#include "Code.hpp"
#include "Function.hpp"
#include <stdlib.h>

int CodeGenerator::structSize = 12;

CodeGenerator::CodeGenerator(const std::string& filename):
	code_(*(new Code(filename))),
	fctDef_(NULL),
	label_(0)
{
	;
}

CodeGenerator::~CodeGenerator()
{
	delete &code_;
}

void CodeGenerator::program_header()
{
	code().setProgramHeader(true);
}

void CodeGenerator::endProgram()
{
	 code().write();
}

void CodeGenerator::function(const std::string& name)
{
	newFct(name);
}

void CodeGenerator::functionArg(const std::string& name) //arguments above 3 can be loaded from address [fp, #(4*argIndex)] when they are used
{
	fct().addArg(name);
}

void CodeGenerator::var(const std::string& name)
{
	if(isFctDef()) //we are in a function definition
	{
		std::ostringstream& o = fct().code();
		unsigned index = fct().argIndex(name);
		if(index < fct().argSize()) //this is a function argument
		{
			if(index < 4)
			{
				o<<"mov r4, r"<<index<<std::endl;
			}
			else
			{
				o<<"ldr r4, [fp, #"<<(4*(index-3))<<"]"<<std::endl;
			}
		}
		else //this is not a function argument
		{
			if(!isGlobal(name))
			{
				addGlobal(name);
			}
			o<<"ldr r4, .globals+"<<code().globalOffset(name)<<std::endl;
		}
		o<<"str r4, [sp, #-4]!"<<std::endl; //push the variable on the stack
	}
	else
	{
		if(!isGlobal(name))
		{
			addGlobal(name);
		}
		currentCode()<<"ldr r4, .globals+"<<code().globalOffset(name)<<std::endl
			<<"str r4, [sp, #-4]!"<<std::endl; //push the variable on the stack
	}
}

void CodeGenerator::integer(const std::string& value)
{
	pushStackScalar(value, 3);
}

void CodeGenerator::Float(const std::string& value)
{
	pushStackScalar(value, 2);
}

void CodeGenerator::pushStackScalar(const std::string& value, unsigned type)
{
	calloc();
	float f = (float) atof(value.c_str());
	int* p = (int*) (&f);
	currentCode()<<"mov r5, "<<*p<<std::endl
		<<"str r5, [r9]"<<std::endl
		<<"mov r5, #"<<type<<std::endl;
	pushStack();
}

void CodeGenerator::string(const std::string& value)
{
	calloc();
	currentCode()<<"mov r8, r9"<<std::endl;
	rodata();
	std::string roStringLabel = nextLabel();
	currentCode()<<roStringLabel<<":"<<std::endl
			<<".asciz \""<<value<<"\""<<std::endl;
	text();
	calloc(value.length()+1);
	strCpy("r9",roStringLabel);
	currentCode()<<"mov r5, r9"<<std::endl
		<<"str r5, [r8, #4]"<<std::endl
		<<"mov r5, #1"<<std::endl
		<<"mov r9, r8"<<std::endl;
	pushStack();
}

void CodeGenerator::assign_mark()
{
	//TODO
}

void CodeGenerator::unary_plus()
{
	;
}

void CodeGenerator::unary_minus()
{

}

void CodeGenerator::Not()
{

}

void CodeGenerator::different()
{
	Operator(DIFFERENT);
}

void CodeGenerator::equals()
{
	Operator(EQUALS);
}

void CodeGenerator::eq()
{
	Operator(EQ);
}

void CodeGenerator::ne()
{
	Operator(NE);
}

void CodeGenerator::lazy_or()
{
	startOperator();
}

void CodeGenerator::lazy_and()
{
	startOperator();
}

void CodeGenerator::greater()
{
	Operator(GREATER);
}

void CodeGenerator::greater_equals()
{
	Operator(GREATER_EQUALS);
}

void CodeGenerator::ge()
{

}

void CodeGenerator::gt()
{

}

void CodeGenerator::lower()
{
	Operator(LOWER);
}

void CodeGenerator::lower_equals()
{
	Operator(LOWER_EQUALS);
}

void CodeGenerator::le()
{

}

void CodeGenerator::lt()
{

}

void CodeGenerator::lexicographicOrder()
{
	startOperator();
}

void CodeGenerator::plus()
{
	Operator(PLUS);
}

void CodeGenerator::minus()
{
	Operator(MINUS);
}

void CodeGenerator::Operator(Type type)
{
	startOperator();

	std::string firstLabel = nextLabel(),
		secondLabel = nextLabel(),
		thirdLabel = nextLabel(),
		fourthLabel = nextLabel();

		currentCode()<<"cmp r5, #1"<<std::endl
		<<"bne "<<firstLabel<<std::endl
		<<"ldr r5, [r4, #4]"<<std::endl
		<<"str r0, [sp, #-4]"<<std::endl
		<<"mov r0, r5"<<std::endl
		<<"bl atof(PLT)"<<std::endl
		<<"mov r5, r0"<<std::endl
		<<"ldr r0, [sp, #-4]"<<std::endl
		<<"b "<<secondLabel<<std::endl
		<<firstLabel<<":"<<std::endl
		<<"ldr r5, [r4]"<<std::endl
		<<secondLabel<<":"<<std::endl
		<<"cmp r7, #1"<<std::endl
		<<"bne "<<thirdLabel<<std::endl
		<<"ldr r7, [r6, #4]"<<std::endl
		<<"str r0, [sp, #-4]"<<std::endl
		<<"mov r0, r7"<<std::endl
		<<"bl atof(PLT)"<<std::endl
		<<"mov r7, r0"<<std::endl
		<<"ldr r0, [sp, #-4]"<<std::endl
		<<"b "<<fourthLabel<<std::endl
		<<thirdLabel<<":"<<std::endl
		<<"ldr r7, [r6]"<<std::endl
		<<fourthLabel<<":"<<std::endl;

	int i;
	if (type == PLUS)
	{
		currentCode()<<"add r5, r5, r7"<<std::endl;
		i = 2;
	}
	else if (type == MINUS)
	{
		currentCode()<<"sub r5, r7, r5"<<std::endl;
		i = 2;
	}
	else if (type == TIMES)
	{
		currentCode()<<"mult"<<std::endl;
		i = 2;
	}
	else if (type == DIVIDE)
	{
		currentCode()<<"div"<<std::endl;
		i = 2;
	}
	else
	{
		std::string fifthLabel = nextLabel(), sixthLabel = nextLabel();
		if (type == GREATER || type == GREATER_EQUALS)
		{
			currentCode()<<"cmp r7, r5"<<std::endl;
		}
		else
		{
			currentCode()<<"cmp r5, r7"<<std::endl;
		}
		if (type == GREATER || type == LOWER)
		{
			currentCode()<<"bgt "<<fifthLabel<<std::endl
				<<"placeholder";//TODO
		}
		else
		{
			currentCode()<<"bge "<<fifthLabel<<std::endl
					<<"placeholder";//TODO
		}
		currentCode()<<std::endl;

		i = 1;
	}

	calloc();
	currentCode()<<"str r5, [r9";
	if (i == 1)
	{
		currentCode()<<", #4";
	}
	currentCode()<<"]"<<std::endl
		<<"mov r5, #"<<i<<std::endl;
	pushStack();
}

void CodeGenerator::concat_mark()
{
	startOperator();
}

void CodeGenerator::startOperator()
{
	currentCode()<<"ldr r4, [sp]"<<std::endl
		<<"add sp, sp, 4"<<std::endl
		<<"ldr r5, [r4, #8]"<<std::endl
		<<"ldr r6, [sp]"<<std::endl
		<<"add sp, sp, 4"<<std::endl
		<<"ldr r7, [r6, #8]"<<std::endl;
}

void CodeGenerator::strCpy(const std::string& destination, const std::string& source)
{
	currentCode()<<"stmfd sp!, {r0, r1}"<<std::endl
			<<"mov r0, "<<destination<<std::endl
			<<"mov r1, "<<source<<std::endl
			<<"bl strcpy(PLT)"<<std::endl
			<<"ldmfd sp!, {r0, r1}"<<std::endl;
}

void CodeGenerator::rodata()
{
	currentCode()<<".section .rodata"<<std::endl
			<<".align"<<std::endl;
}

void CodeGenerator::text()
{
	currentCode()<<".text"<<std::endl
			<<".align"<<std::endl;
}

void CodeGenerator::calloc() //allocates a struct, address is put in r9
{
	calloc(structSize);
}

void CodeGenerator::calloc(unsigned size) //allocates size bytes, address is put in r9
{
	currentCode()<<"stmfd sp!, {r0, r1}"<<std::endl
		<<"mov r0, #1"<<std::endl
		<<"mov r1, #"<<size<<std::endl
		<<"bl calloc(PLT)"<<std::endl
		<<"mov r9, r0"<<std::endl
		<<"ldmfd sp!, {r0, r1}"<<std::endl;
}

void CodeGenerator::pushStack()
{
	currentCode()<<"str r5, [r9, #8]"<<std::endl //type = 0 (UNDEF), 1 (STRING), 2 (FLOAT), 3 (INT)
		<<"str r9, [sp, #-4]!"<<std::endl; //push the variable on the stack
}

void CodeGenerator::endFunction()
{
	unsetFctDef();
}

std::string CodeGenerator::nextLabel()
{
	std::ostringstream res;
	++label_;
	res<<".L"<<label_;
	return res.str();
}

void CodeGenerator::functionCall(const std::string& name)
{
	//TODO
}

bool CodeGenerator::isGlobal(const std::string& name) const
{
	return code().isGlobal(name);
}

void CodeGenerator::addGlobal(const std::string& name)
{
	code().addGlobal(name);
}

const std::string& CodeGenerator::fctDefName() const { return fct().name(); }
Function& CodeGenerator::fct() const { return *fctDef_; }
void CodeGenerator::newFct(std::string name)
{
	fctDef_ = new Function(name);
	code().addFunction(*fctDef_);
}
void CodeGenerator::unsetFctDef() { fctDef_ = NULL; }
bool CodeGenerator::isFctDef() const { return fctDef_ != NULL; }

Code& CodeGenerator::code() const
{
	return code_;
}

std::ostringstream& CodeGenerator::currentCode()
{
	Function* fp;
	if(isFctDef())
	{
		fp = (&fct());
	}
	else
	{
		fp = &(code().main());
	}
	return fp->code();
}



