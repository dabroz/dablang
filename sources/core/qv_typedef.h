#pragma once

class qTypedef : public qValue
{
public:

	qTypedef(qValue * xxname, qValue * xxtype);
	virtual qString print(int indent = 0);

	virtual bool IsNoValue() { return true; }
};
