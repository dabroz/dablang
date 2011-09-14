#include "stdafx.h"
#include "dab_header.h"

void qDeclare::gatherVariables()
{
	/*qProgram * prog = dynamic_cast<qProgram*>(parent);
	if (prog)
	{
		vartype = VAR_GLOBAL;
		real_name = "_g_" + pretty_name;

		prog->globalvars[pretty_name] = this;

		return;
	}*/
	qSequence * seq = dynamic_cast<qSequence*>(parent);
	if (seq)
	{
		qFunction * fun = dynamic_cast<qFunction*>(seq->parent);
		if (fun)
		{
			// variable in arg list
			vartype = VAR_ARG;
			real_name = "_a_" + pretty_name;
			fun->variablesavail.push_back(this);
			return;
		}
	}
	// local var
	char nn[128];
	sprintf(nn, "_l_%08X_", this);
	vartype = VAR_LOCAL;
	real_name = qString(nn) + pretty_name;

	parent->variablesavail.push_back(this);
	
	qValue::gatherVariables();
}

std::vector<qDeclare*> llvmglobalvars;

bool qDeclare::LLVM_build( llvm::Module * module )
{
	return false;
}

void qDeclare::LLVM_prebuild( llvm::Module * module )
{
	llvm::Type * t = neu_type->llvm();

	Constant * v = UndefValue::get(t);

	if (L()) v = dynamic_cast<Constant*>(L()->BuildValue());

	llvmvar = new llvm::GlobalVariable(*module, t, neu_type->is_const , 
		neu_type->is_const ? llvm::GlobalVariable::InternalLinkage :
		llvm::GlobalVariable::ExternalLinkage, v, name);

	llvmglobalvars.push_back(this);
}

qDeclare::qDeclare( qValue * _type, qValue * _name, qValue * _value )
{
	this->neu_type = _type->neu_type;
	if (_name) this->name = _name->name;		
	if (_value) insert(_value);

	pretty_name = name;
	llvmvar = 0;
	vartype = -1;
	dataptr = 0;
}

qString qDeclare::print( int indent )
{
	qString ret = doIndent(indent) + printType(neu_type) + " $" + name;
	
	if (size())
	{
		ret += " = " + L()->print(0);
	}

	if (indent)
		ret += ";";

	return ret;
}
