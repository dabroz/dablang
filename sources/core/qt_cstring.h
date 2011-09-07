#pragma once

class qneu_CStringType : public qneu_Type
{
public:
	virtual qneu_Type * CreateConst() { return this; }
	virtual qString name() const { return "cstring"; }
	virtual qString mangle() const { return "s"; }
	qneu_CStringType() {  }
	virtual llvm::Type * llvm()
	{
		return Type::getInt8PtrTy(getGlobalContext());
	}
	virtual bool can_cast_to(qneu_Type * other) const 
	{
		if (other->isPointer()) return true;
		return false;
	}
	static qneu_CStringType * get() { static qneu_CStringType * ret = new qneu_CStringType(); ret->is_const = true; return ret; }
};
