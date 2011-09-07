#pragma once

class qSubvariable : public qValue
{
public:
	qSubvariable(qValue *var, qValue * memb)
	{
		insert(var);
		name = memb->name;
	}
	virtual qString print(int indent = 0) { return "("+L()->print() + ")." + name; }

	virtual void subupdateType();
	virtual Value * getLlvmVariable();
	virtual llvm::Value * BuildValue() ;
};
