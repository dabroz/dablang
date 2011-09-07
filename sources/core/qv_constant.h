#pragma once

class qConstant : public qValue
{
public:
	qConstant(int vtype, int v);
	qConstant(int vtype, float v);
	qConstant(int vtype, bool v);
	qString subdump();
	qString print(int indent);
	virtual llvm::Value * BuildValue() ;
};
