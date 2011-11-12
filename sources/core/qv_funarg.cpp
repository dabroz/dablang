#include "stdafx.h"
#include "dab_header.h"

qString qFunctionArgument::print( int indent )
{
	return "funarg? " + _argName;
}

qFunctionArgument::qFunctionArgument( qFunction * fun, const qString & name )
{
	_argFunction = fun;
	_argName = name;
	for (int i = 0; i < fun->L()->size(); i++)
	{
		if (fun->L()->children[i]->name == name)
			neu_type = fun->L()->children[i]->neu_type;
	}
}

llvm::Value * qFunctionArgument::BuildValue()
{
	return function()->VarArg("_a_"+_argName);
}
