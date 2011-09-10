#include "stdafx.h"
#include "dab_header.h"

qGlobalVariable::qGlobalVariable( qValue * _type, qValue * _name, qValue * _value )
{

}

qString qGlobalVariable::print( int indent )
{
	return "global $" + name + "$";
}

void qGlobalVariable::gatherVariables()
{

}

void qGlobalVariable::LLVM_prebuild( llvm::Module * module )
{

}

bool qGlobalVariable::LLVM_build( llvm::Module * module )
{
	return false;
}
