#pragma once

class qAssign : public qInstruction
{
public:
	qAssign(qValue * var, qValue * value);
	qString print(int indent);
	virtual bool LLVM_build(llvm::Module * module) ;
	virtual void subupdateType();
};
