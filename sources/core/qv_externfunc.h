#pragma once

class qExternFunc : public qFunction
{
public:

	qValueVec _options;

	qExternFunc(qValue * options, qValue * _type, qValue * _name, qValue * params);
	qString print(int indent);
	virtual void LLVM_prebuild(llvm::Module * module) ;
	bool LLVM_build( llvm::Module * module ){return false;}
	virtual void LLVM_update() {}
};
