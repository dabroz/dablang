#pragma once

class qUnOp : public qValue
{
public:
	qUnOp(const char * _name, qValue * v);
	qString print(int indent);
	virtual void subupdateType();
	virtual llvm::Value * BuildValue() ;
};

