#include "stdafx.h"
#include "dab_header.h"
#include "dab_internal.h"

Value * qVariable::getLlvmVariable()
{
	return function()->getVariable(realname);
}

llvm::Value * qVariable::BuildValue()
{
	/*Value * varg = function()->VarArg(realname);
	if (varg) 
	{
		return varg;
	}*/
	dab_Module::it_g it = this->the_module->_globals.find(name);
	if (it != this->the_module->_globals.end())
	{
		return it->second->getLlvmVariable();
	}

	Value * var = getLlvmVariable();

	if (!var) 
	{
		error("No (local) llvm variable");
	}

	if (dynamic_cast<qneu_ArrayType*>(neu_type))
	{
		return var;
	}

	return Builder.CreateLoad(var, false, name);
}
