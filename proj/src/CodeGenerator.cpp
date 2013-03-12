#include "CodeGenerator.hpp"
#include "Function.hpp"

CodeGenerator::CodeGenerator(const std::string& filename):
	file_(),
	filename_(filename),
	fctDef_(NULL),
	fct_(NULL),
	fctMap_()
{
	file().open(filename.c_str());
}

CodeGenerator::~CodeGenerator()
{
	// TODO Auto-generated destructor stub
}

std::ofstream& CodeGenerator::file()
{
	return file_;
}

const std::string& CodeGenerator::filename()
{
	return filename_;
}

void CodeGenerator::program_header()
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

void CodeGenerator::endProgram()
{
	 file()<<".ident \"GCC: (GNU) 4.6 20120106 (prerelease)\""<<std::endl
		<<".section .note.GNU-stack,"",%progbits"<<std::endl;
}

void CodeGenerator::text()
{
	file()<<".text"<<std::endl
		<<".align 2"<<std::endl;
}

void CodeGenerator::rodata()
{
	file()<<"section .rodata"<<std::endl
		<<".align 2"<<std::endl;
}

void CodeGenerator::function(const std::string& name)
{
	newFct(name);
	file()<<".global "<<fctDefName()<<std::endl
		<<".type "<<fctDefName()<<", %function"<<std::endl
		<<fctDefName()<<":"<<std::endl
		<<"stmfd sp!, {fp, lr, r4, r5, r6, r7, r8, r9, r10, r11}"<<std::endl //save all registers
		<<"add fp, sp, #36"<<std::endl; //set fp to point to the first stack address this function owns
}

void CodeGenerator::functionArg(const std::string& name) //arguments above 3 can be loaded from address [fp, #(4*argIndex)] when they are used
{
	fctDef().addArg(name);
	//TODO LocalVariable class
}

// !!!!! mettre les variables sur le stack comme une machine en polonaise inversée !!!!!
// !!!!! c'est le seul moyen de pouvoir resoudre des trucs comme 5 + 4 * 7 + 3 +...
// !!!!! operateur = pop les deux premiers elements du stack, appliquer l'operation, push le resultat

void CodeGenerator::var(const std::string& name)
{
	if(isFctDef())
	{
		unsigned index = fct().argIndex(name); //erreur possible : variable non definie
		//TODO verif variable globale
		if(index < 4)
		{
			file()<<"mov r4, r"<<index<<std::endl;
		}
		else
		{
			file()<<"ldr r4, [fp, #"<<(4*index)<<"]"<<std::endl;
		}
		file()<<"str r4, [sp, #-4]!"<<std::endl; //push the variable on the stack
	}
}

void CodeGenerator::endFunction()
{
	file()<<"ldmfd sp!, {fp, lr, r4, r5, r6, r7, r8, r9, r10, r11}"<<std::endl
		<<".size "<<fctDefName()<<", .-"<<fctDefName()<<std::endl;
	unsetFctDef();
}

void CodeGenerator::functionCall(const std::string& name)
{
	setFct(name);
	//TODO
}

void CodeGenerator::setFct(const std::string& name)
{
	fct_ = *(fctMap()[name]);
}

const std::string& CodeGenerator::fctDefName() const { return fctDef().name(); }
Function& CodeGenerator::fctDef() const { return *fctDef_; }
Function& CodeGenerator::fct() const { return *fct_; }
std::map<std::string,Function*>& CodeGenerator::fctMap() { return fctMap_; }
void CodeGenerator::newFct(std::string name)
{
	fctDef_ = new Function(name);
	fctMap()[name] = fctDef_;
}
void CodeGenerator::unsetFctDef() { fctDef_ = NULL; }
bool CodeGenerator::isFctDef() const { return fctDef_ != NULL; }


