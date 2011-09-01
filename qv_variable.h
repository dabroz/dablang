#pragma once

class qVariable : public qValue
{
public:
	qString realname;

	qVariable(qValue * id)
	{
		if (id)
			name = id->name;
	}
	qString print(int indent)
	{
		return "$" + name;
	}

	qString subdump() { return realname; }

	virtual Value * getLlvmVariable();
	virtual llvm::Value * BuildValue() ;
};
