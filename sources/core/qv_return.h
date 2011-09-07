#pragma once

class qReturn : public qInstruction
{
public:
	qReturn(qValue * v)
	{
		insert(v);
	}
	qString print(int indent)
	{
		return doIndent(indent) + "return " + L()->print(0) + ";";
	}

	void subupdateType()
	{
		neu_type = L()->neu_type;
	}
	virtual bool LLVM_build(llvm::Module * module) ;
};
