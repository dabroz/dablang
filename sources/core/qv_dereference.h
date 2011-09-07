#pragma once

class qDereference : public qValue
{
public:
	qDereference(qValue * base) { insert(base); }
	qString print(int indent);
	virtual void subupdateType();
	virtual llvm::Value * BuildValue() ;
	virtual Value * getLlvmVariable();
};

