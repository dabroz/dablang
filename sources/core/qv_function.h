#pragma once

class qFunction : public qValue
{
public:
	qneu_Function * func;

	//llvm::Value * VarArg(qString mangledName);
	llvm::Value * VarLocal(qString mangledName);
	//llvm::Value * VarGlobal( qString realname );
	llvm::Value * getVariable(qString realname);

	qFunction(qValue* _type, qValue* _name, qValue* _arglist, qValue* _body);
	qString print(int indent);

	virtual void LLVM_prebuild(llvm::Module * module);
	virtual bool LLVM_build(llvm::Module * module) ;
	virtual void LLVM_update();

protected:
	llvm::Function *CreateFun(llvm::Module *module);
	void InsertArgs( llvm::Function * F );
	qFunction() { func = 0; }
};
