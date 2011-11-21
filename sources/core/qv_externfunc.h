#pragma once

class qExternFunc : public qFunction
{
public:

	std::map<qString, qString> _options;
	//qValueVec _options;

	qExternFunc(qValue * options, qValue * _type, qValue * _name, qValue * params, int shortversion = 0);
	qString print(int indent);
	virtual void LLVM_prebuild(llvm::Module * module) ;
	bool LLVM_build( llvm::Module * module );
	virtual void LLVM_update() {}
};
