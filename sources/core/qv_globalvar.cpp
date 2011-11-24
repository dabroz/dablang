#include "stdafx.h"
#include "dab_header.h"
#include "dab_internal.h"

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
Value * QEMPTY=0;
bool qGlobalVariable::LLVM_build( llvm::Module * module )
{
	llvm::Type * t = neu_type->llvm();

	Constant * v = UndefValue::get(t);

	if (L()) v = dynamic_cast<Constant*>(L()->BuildValue());

	if (name=="EMPTY_WND_PROC")
	{
		llvmvar=0;

		/*DefWindowProc(hWnd,uMsg,wParam,lParam);*/
		Type*  itype = Type::getInt32Ty(getGlobalContext());
		std::vector<Type*>types;
		types.push_back(itype);
		types.push_back(itype);
		types.push_back(itype);
		types.push_back(itype);
		FunctionType * ftyp = FunctionType::get(itype,types,false);
		Function * deff=Function::Create(ftyp,llvm::Function::ExternalLinkage,"DefWindowProcA", module);
		deff->setCallingConv(CallingConv::X86_StdCall);

		Function * empty = Function::Create(ftyp, llvm::Function::ExternalLinkage,"EMPTY_WND_PROC", module);
		BasicBlock * b = BasicBlock::Create(getGlobalContext(), "entry", empty);
		Builder.SetInsertPoint(b);
		std::vector<Value*>vv;

		for (Function::arg_iterator AI = empty->arg_begin(); AI!=empty->arg_end();AI++)
		vv.push_back(AI);

Value * v = Builder.CreateCall(deff,vv,"");
		Builder.CreateRet(v);

		QEMPTY=empty;
	}
	else{
	llvmvar = new llvm::GlobalVariable(*module, t, neu_type->is_const , 
		neu_type->is_const ? llvm::GlobalVariable::InternalLinkage :
		llvm::GlobalVariable::ExternalLinkage, v, name);
	}

	//qdtprintf("EMITED GLOBAL `%s` const %d\n", name.c_str(), neu_type->is_const);

	return false;
}

llvm::Value * qGlobalVariable::getLlvmVariable()
{
	return llvmvar;
}
