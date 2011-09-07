#pragma once

class qFuncall : public qValue
{
public:
	bool mangled;
	class qneu_Function * func;

	qFuncall(qValue * _name, qValue * _arglist);

	qString subdump();
	qString print(int indent);

	virtual void subupdateType();

	virtual llvm::Value * BuildValue() ;
	llvm::Value * CreateSubvalue(bool named);
	bool LLVM_build( llvm::Module * module );
};
