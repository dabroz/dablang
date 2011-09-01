#pragma once

class qStackalloc : public qValue
{
public:
	qString print(int indent)
	{
		qString ret = doIndent(indent) + "STACK ALLOC\n";
		for (size_t i = 0, e = size(); i < e; i++)
		{
			ret += (*this)[i]->print(indent) + "\n";			
		}
		return ret;
	}

	virtual bool LLVM_build(llvm::Module * module);
	virtual bool IsNoValue() { return true; }
};
