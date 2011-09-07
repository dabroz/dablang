#pragma once

class qPointer : public qValue
{
public:
	qPointer(qValue * base) { insert(base); }
	qString print(int indent) { return "&(" + L()->print() + ")"; }
	virtual void subupdateType();
	virtual llvm::Value * BuildValue() ;
};

