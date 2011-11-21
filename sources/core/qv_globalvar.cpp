#include "stdafx.h"
#include "dab_header.h"

qGlobalVariable::qGlobalVariable( qValue * _type, qValue * _name, qValue * _value )
{
	name = _name->name;
	neu_type = _type->neu_type;
	if (_value)
		insert(_value);
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
	llvm::Type * t = neu_type->llvm();

	Constant * v = UndefValue::get(t);

	if (L()) v = dynamic_cast<Constant*>(L()->BuildValue());

	llvmvar = new llvm::GlobalVariable(*module, t, neu_type->is_const , 
		neu_type->is_const ? llvm::GlobalVariable::InternalLinkage :
		llvm::GlobalVariable::ExternalLinkage, v, name);

	qdtprintf("EMITED GLOBAL `%s` const %d\n", name.c_str(), neu_type->is_const);

	return false;
}

llvm::Value * qGlobalVariable::getLlvmVariable()
{
	return llvmvar;
}
