#pragma once

class DABCORE_API qneu_VarargType : public dt_BaseType
{
public:
	virtual qString name() const { return "vararg"; }
	virtual qString mangle() const { return "v"; }
	virtual bool isVararg() const { return true; }
	static qneu_VarargType * get() { static qneu_VarargType * ret = new qneu_VarargType; return ret; }

	virtual Type * llvm() { qdterror("LLVM VARARG!"); return 0; }
private:
	qneu_VarargType() { }
};
