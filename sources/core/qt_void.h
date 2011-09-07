#pragma once

class qneu_VoidType : public qneu_Type
{
public:
	qneu_VoidType() { }
	virtual bool isVoid() const { return true; }
	virtual qString name() const { return "void"; }
	virtual llvm::Type * llvm();

	static qneu_VoidType * get() { static qneu_VoidType * ret = new qneu_VoidType(); return ret; }
};
