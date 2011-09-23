#pragma once

class qFunctionArgument : public qValue
{
public:
	qFunctionArgument(qFunction * fun, const qString & name);

	qFunction * _argFunction;
	qString _argName;

	qString print(int indent);
	qString subdump() { return _argName; }
};
