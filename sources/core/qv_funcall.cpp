#include "stdafx.h"
#include "dab_header.h"
#include "dab_internal.h"

Value * qFuncall::CreateSubvalue(bool named)
{
	if (!func) 
	{
		qdterror("NO FUN FOR `%s`", name.c_str());
	}	
	std::vector<Value*> args;

	for (int i = 0; i < L()->size(); i++)
	{
		Value * v = L()->children[i]->BuildValue();

		if (!v) 
		{
			qdterror("No L v for fun");
		}

		if (func->isvararg() && func->args.size() <= i)
		{
			if (v->getType() == Type::getFloatTy(getGlobalContext()))
			{
				v = Builder.CreateFPCast(v, Type::getDoubleTy(getGlobalContext()));
			}
		}

		args. push_back(v);
	}

	CallInst * ci = 0;

	Value * callee = func->llvmd;

	if (!dynamic_cast<Function*>(callee))
	{
		callee = Builder.CreateLoad(callee);
	}

	if (args.size()) 
		ci = Builder.CreateCall(callee, llvm::ArrayRef<Value*>(args), named?name:"");
	else
		ci = Builder.CreateCall(callee, named?name:"");

	/*if (!dynamic_cast<Function*>(callee))
	{
	}
	else
	{*/

	//qdtprintf("CALL %s\n", func->name.c_str());
	if (func->name.find("gl")==0)
	{
		ci->setCallingConv(CallingConv::X86_StdCall);
	}
//else if (dynamic_cast<Function*>(func->llvmd))
//{
	else	ci->setCallingConv(((Function*)func->llvmd)->getCallingConv());
//}
//else 
	//}

	return ci;
}

llvm::Value * qFuncall::BuildValue()
{
	Value * v = CreateSubvalue(true);
	return v;
}

bool qFuncall::LLVM_build( llvm::Module * module )
{
	CreateSubvalue(false);
	return false;
}

qString qFuncall::print( int indent )
{
	qString r = doIndent(indent) + "call "+name+"(";
	if (L())
	{
		for (int i = 0, e = L()->size(); i != e; i++)
		{
			if (i) r+=", ";
			r += L()->children[i]->print();
		}
	}
	r += ")";
	return r;
}

qString qFuncall::subdump()
{
	if (!func) return ""; return func->mangled_name;
}

qFuncall::qFuncall( qValue * _name, qValue * _arglist )
{
	func = 0;
	mangled = false;
	name = _name->name;
	if (_arglist)
		insert(_arglist);
	else 
		insert(new qSequence());
}
