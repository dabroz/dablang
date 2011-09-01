#include "qdt3.h"

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
		qdterror("No llvm variable for '%s'\n", print(0).c_str());
	}

	if (dynamic_cast<qneu_ArrayType*>(neu_type))
	{
		return var;
	}

	return Builder.CreateLoad(var, false, name);
}
