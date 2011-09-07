#pragma once

class DABCORE_API qneu_CStringType : public dt_BaseType
{
public:
	virtual dt_BaseType * CreateConst() { return this; }
	virtual qString name() const { return "cstring"; }
	virtual qString mangle() const { return "s"; }
	qneu_CStringType() {  }
	virtual llvm::Type * llvm();
	virtual bool can_cast_to(dt_BaseType * other) const 
	{
		if (other->isPointer()) return true;
		return false;
	}
	static qneu_CStringType * get() { static qneu_CStringType * ret = new qneu_CStringType(); ret->is_const = true; return ret; }
};
