#pragma once

class qGlobalVariable : public qValue
{
public:
	llvm::Value * llvmvar;
	void * dataptr;

	qGlobalVariable(qValue * _type, qValue * _name, qValue * _value);

	qString print(int indent);

	virtual void gatherVariables();

	virtual void LLVM_prebuild(llvm::Module * module);
	virtual bool LLVM_build(llvm::Module * module) ;
};
