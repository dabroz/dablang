#pragma once

class qTypeHolder : public qValue 
{
public:
	qTypeHolder(dt_BaseType * t) { neu_type = t; }
	virtual qString print(int indent = 0) { return "TYPEHOLDER"; }
};
