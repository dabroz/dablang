#pragma once

class qIf : public qInstruction
{
public:
	qIf(qValue * _condition, qValue * _then, qValue * _else);

	qString print(int indent);
	virtual bool LLVM_build(llvm::Module * module) ;
	virtual void subupdateType();

	virtual bool IsNoValue() { return true; }
};
