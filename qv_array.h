#pragma once

class qArrayAccess : public qValue
{
public:
	qArrayAccess(qValue *var, qValue * index);
	virtual qString print(int indent = 0);
	virtual void subupdateType();
	virtual Value * getLlvmVariable();
	virtual llvm::Value * BuildValue() ;
};
