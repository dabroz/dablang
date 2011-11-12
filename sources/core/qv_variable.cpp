#include "stdafx.h"
#include "dab_header.h"
#include "dab_internal.h"

Value * qVariable::getLlvmVariable()
{
	return function()->getVariable(realname);
}

llvm::Value * qVariable::BuildValue()
{
	Value * varg = function()->VarArg(realname);
	if (varg) 
	{
		return varg;
	}

	Value * var = getLlvmVariable();

	if (!var) 
	{
		error("No llvm variable");
	}

	if (dynamic_cast<qneu_ArrayType*>(neu_type))
	{
		return var;
	}

	return Builder.CreateLoad(var, false, name);
}
