#pragma once

class qFunction : public qValue
{
public:
	qneu_Function * func;

	Value * VarArg(qString mangledName);
	Value * VarLocal(qString mangledName);
	Value * VarGlobal( qString realname );
	Value * getVariable(qString realname);

	qFunction(qValue* _type, qValue* _name, qValue* _arglist, qValue* _body);
	qString print(int indent);

	virtual void LLVM_prebuild(llvm::Module * module);
	virtual bool LLVM_build(llvm::Module * module) ;
	virtual void LLVM_update();

protected:
	llvm::Function *CreateFun(Module *module);
	void InsertArgs( llvm::Function * F );
	qFunction() { func = 0; }
};
