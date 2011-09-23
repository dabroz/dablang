#pragma once

enum
{
	VAR_GLOBAL,
	VAR_ARG,
	VAR_LOCAL
};

class qDeclare : public qValue
{
public:
	qString pretty_name;
	qString real_name;
	int vartype;
	llvm::Value * llvmvar;
	void * dataptr;

	qDeclare(dt_BaseType * _type, const qString & _name, qValue * _value);
	qDeclare(qValue * _type, qValue * _name, qValue * _value);

	qString print(int indent);
	qString subdump() { return real_name; }

	virtual void gatherVariables();

	virtual void LLVM_prebuild(llvm::Module * module);
	virtual bool LLVM_build(llvm::Module * module) ;
};
