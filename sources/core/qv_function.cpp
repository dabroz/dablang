#include "stdafx.h"
#include "dab_header.h"
#include "dab_internal.h"

using namespace llvm;


llvm::FunctionType *qFunction::GetType()
{
	std::vector<llvm::Type *> params;
	bool vararg = false;
	for (int i = 0; i < func->args.size(); i++)
	{
		dt_BaseType * TT = func->args[i].type;
		if (TT->isVararg()) 
			vararg = true;
		else
		{
			Type * lt = TT->llvm();
			if (!lt)
			{
				qdterror("No LLVM type for %s\n", TT->name().c_str());
			}
			params.push_back(lt);
		}
	}

	Type * lt = func->returntype->llvm();
	if (!lt)
	{
		qdterror("No LLVM type for return %s\n", func->returntype->name().c_str());
	}

	return llvm::FunctionType::get(lt, params, vararg);
}

llvm::Function * qFunction::CreateFun(Module *module)
{
	llvm::Function *F = llvm::Function::Create(GetType(),  llvm::Function::ExternalLinkage, func->mangled_name, module);

	InsertArgs(F);

	return F;
}

//extern std::map<qString, Function*> very_raw_funcs;

void qFunction::LLVM_prebuild( llvm::Module * module )
{
	qdtprintf2("Prebuilding fun `%s`\n", this->name.c_str());

	Function * F = 0;//very_raw_funcs[this->func->mangled_name];
		
	if (F)
	{
		func->llvmd = F;
		F->deleteBody();
		InsertArgs(F);
	}
	else
	{
		F=  CreateFun(module);
		func->llvmd = F;
	}
}

bool qFunction::LLVM_build( llvm::Module * module )
{	
	BasicBlock *BB = BasicBlock::Create(getGlobalContext(), "entry", func->llvmd);

	Builder.SetInsertPoint(BB);

	bool q = false;
	
	if (R()->L())
	{
		 q = R()->L()->LLVM_build(0);
	}
	
	if (!q)
	{
		if (dynamic_cast<qneu_VoidType*>(func->returntype)) 
		{
			Builder.CreateRetVoid();
		}
		else
		{
			Builder.CreateRet(UndefValue::get(func->llvmd->getReturnType()));
		}
	}

	return false;
}

Value * qFunction::VarLocal( qString mangledName )
{
	qStackalloc * st = dynamic_cast<qStackalloc*>(R()->L()->L());
	if (!st) return 0;
	for (int i = 0; i < st->size(); i++)
	{
		qDeclare * decl = dynamic_cast<qDeclare*>(st->children[i]);
		if (decl->real_name == mangledName) return decl->llvmvar;
	}
	return 0;
}

Value * qFunction::getVariable( qString realname )
{
	return VarLocal(realname);
}

void qFunction::LLVM_update()
{
	extern Module * globalllvmmodule;
	extern ExecutionEngine *TheExecutionEngine;

	LLVM_prebuild(globalllvmmodule);
	LLVM_build(globalllvmmodule);

	TheExecutionEngine->recompileAndRelinkFunction(this->func->llvmd);
}

void qFunction::InsertArgs( llvm::Function * F )
{
	unsigned Idx = 0;
	for (Function::arg_iterator AI = F->arg_begin(); AI!=F->arg_end();
		++AI, ++Idx) {
			AI->setName(func->args[Idx].name);
			func->args[Idx].llvmreef = AI;
	}
}

qFunction::qFunction( qValue* _type, qValue* _name, qValue* _arglist, qValue* _body )
{
	func = 0;

	this->neu_type = _type->neu_type;
	this->name = _name->name;

	if (!_arglist)
	{
		_arglist = new qSequence();
	}

	insert(_arglist);

	if (!_body)
	{
		insert(new qSequence());
	}
	else insert(_body);
}

qString qFunction::print( int indent )
{
	qString ret = printType(neu_type) + " " + name + "(";
	for (size_t i = 0, e = L()->size(); i < e; i++)
	{
		if (i) ret += ", ";
		ret += (*L())[i]->print(0);			
	}
	ret += ")\n" + R()->print(0);
	return ret;
}
