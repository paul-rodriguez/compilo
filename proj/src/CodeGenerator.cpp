#include "CodeGenerator.hpp"
#include "Code.hpp"
#include "Function.hpp"

CodeGenerator::CodeGenerator(const std::string& filename):
	code_(*(new Code(filename))),
	fctDef_(NULL)
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
	currentCode()<<"mov r0, #1"<<std::endl
		<<"mov r1, #12"<<std::endl
		<<"bl calloc(PLT)"<<std::endl
		<<"mov r4, r0"<<std::endl
		<<".set r5, "<<value<<std::endl
		<<"str r5, [r4]"<<std::endl //number = r5
		<<"mov r5, #3"<<std::endl
		<<"str r5, [r4, #8]"<<std::endl //type = 3 (INT)
		<<"str r4, [sp, #-4]!"<<std::endl; //push the variable on the stack
}

void CodeGenerator::endFunction()
{
	unsetFctDef();
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



