#pragma once

class qWhile : public qInstruction
{
public:
	qWhile(qValue * _condition, qValue * _repeat);
	qString print(int indent);
	virtual bool LLVM_build(llvm::Module * module) ;
	virtual void subupdateType();
};
