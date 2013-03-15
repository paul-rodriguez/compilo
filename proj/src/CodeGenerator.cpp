#include "CodeGenerator.hpp"
#include "Code.hpp"
#include "Function.hpp"
#include <stdlib.h>

int structSize = 12;

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
	//TODO LocalVariable class
}

// !!!!! mettre les variables sur le stack comme une machine en polonaise inversée !!!!!
// !!!!! c'est le seul moyen de pouvoir resoudre des trucs comme 5 + 4 * 7 + 3 +...
// !!!!! operateur = pop les deux premiers elements du stack, appliquer l'operation, push le resultat

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
	currentCode()<<"mov r5, "<<<<std::endl
		<<"str r5, [r9, #4]"<<std::endl // faire qqch!
		<<"mov r5, #1"<<std::endl;
	pushStack();
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
	Operator(Type::DIFFERENT);
}

void CodeGenerator::equals()
{
	Operator(Type::EQUALS);
}

void CodeGenerator::eq()
{
	Operator(Type::EQ);
}

void CodeGenerator::ne()
{
	Operator(Type::NE);
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
	Operator(Type::GREATER);
}

void CodeGenerator::greater_equals()
{
	Operator(Type::GREATER_EQUALS);
}

void CodeGenerator::ge()
{

}

void CodeGenerator::gt()
{

}

void CodeGenerator::lower()
{
	Operator(Type::LOWER);
}

void CodeGenerator::lower_equals()
{
	Operator(Type::LOWER_EQUALS);
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
	if (type == Type::PLUS)
	{
		currentCode()<<"add r5, r5, r7"<<std::endl;
		i = 2;
	}
	else if (type == Type::MINUS)
	{
		currentCode()<<"sub r5, r7, r5"<<std::endl;
		i = 2;
	}
	else if (type == Type::TIMES)
	{
		currentCode()<<"mult"<<std::endl;
		i = 2;
	}
	else if (type == Type::DIVIDE)
	{
		currentCode()<<"div"<<std::endl;
		i = 2;
	}
	else
	{
		std::string fifthLabel = nextLabel(), sixthLabel = nextLabel();
		if (type == Type::GREATER || type == Type::GREATER_EQUALS)
		{
			currentCode()<<"cmp r7, r5"<<std::endl;
		}
		else
		{
			currentCode()<<"cmp r5, r7"<<std::endl;
		}
		if (type == Type::GREATER || type == Type::LOWER)
		{
			currentCode()<<"bgt "<<fifthLabel<<std::endl
				<<
		}
		else
		{
			currentCode()<<"bge "<<fifthLabel<<std::endl
				<<
		}
		currentCode()<<std::endl

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

void CodeGenerator::calloc()
{
	currentCode()<<"str r0, [sp, #-4]!"<<std::endl
		<<"mov r0, #1"<<std::endl
		<<"mov r1, #"<<structSize<<std::endl
		<<"bl calloc(PLT)"<<std::endl
		<<"mov r9, r0"<<std::endl
		<<"ldr r0, [sp]"<<std::endl
		<<"add sp, sp, 4"<<std::endl;
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



