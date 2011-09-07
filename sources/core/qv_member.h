#pragma once

class qMember : public qValue
{
public:
	qMember(qValue * xtype, qValue * xname)
	{
		neu_type = xtype->neu_type;
		name = xname->name;
	}
	virtual qString print(int indent = 0) { return doIndent(1) + printType(neu_type) + " " + name + ";"; }
};
