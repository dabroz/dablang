#pragma once

class qBreak : public qValue
{
public:
	qBreak() { qdterror("DONT USE BREAK, NOT IMPLEMENTED"); }
	qString print(int indent) { return "break"; }

	virtual bool IsNoValue() { return true; }
};
