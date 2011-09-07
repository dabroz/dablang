#pragma once

class DABCORE_API qneu_VoidType : public dt_BaseType
{
public:
	qneu_VoidType() { }
	virtual bool isVoid() const { return true; }
	virtual qString name() const { return "void"; }
	virtual llvm::Type * llvm();

	static qneu_VoidType * get() { static qneu_VoidType * ret = new qneu_VoidType(); return ret; }
};
