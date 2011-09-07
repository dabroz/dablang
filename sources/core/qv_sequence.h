#pragma once

class qSequence : public qValue
{
public:
	qString print(int indent)
	{
		qString ret;
		for (size_t i = 0, e = size(); i < e; i++)
		{
			ret += (*this)[i]->print(indent) + "\n";			
		}
		return ret;
	}
	virtual bool LLVM_build(llvm::Module * module) 
	{
		for (int i =0 ;i<size();i++)
		{
			bool q = children[i]->LLVM_build(module);
			if (q) return true;
		}
		return false;
	}
	virtual bool IsNoValue() { return true; }
};
