#pragma once

class qBlock : public qInstruction
{
public:
	qBlock(qValue * v)
	{
		insert(v);
	}
	qString print(int indent)
	{
		return doIndent(indent) + "{\n" + L()->print(indent+1) + doIndent(indent) + "}";
	}
	bool isBlock() { return true; }
	virtual bool LLVM_build(llvm::Module * module) { return L()->LLVM_build(module); }

	virtual bool IsNoValue() { return true; }
};
