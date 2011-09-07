#pragma once

class qBinOp : public qValue
{
public:
	qBinOp(const char * _name, qValue * left, qValue * right);
	qString print(int indent);

	virtual void subupdateType();
	virtual llvm::Value * BuildValue() ;
};
