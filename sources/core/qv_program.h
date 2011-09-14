#pragma once

class qProgram : public qSequence
{
public:
	//std::map<qString, qDeclare*> globalvars;

	virtual bool LLVM_build(llvm::Module * module);
	virtual void LLVM_prebuild(llvm::Module * module);

	void AppendProgram(qProgram * prog);
};
