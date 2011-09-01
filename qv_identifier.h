#pragma once

class qIdentifier : public qValue
{
public:
	qIdentifier(const char * v)
	{
		name = v;
	}
	qString print(int indent)
	{
		return doIndent(indent) + ",," + name + "''";
	}
};
