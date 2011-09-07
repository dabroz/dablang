#pragma once

class qTypeHolder : public qValue 
{
public:
	qTypeHolder(qneu_Type * t) { neu_type = t; }
	virtual qString print(int indent = 0) { return "TYPEHOLDER"; }
};
