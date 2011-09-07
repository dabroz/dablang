#pragma once

class qInstruction : public qValue
{
public:
	bool isInstruction() { return true; }

	virtual bool IsNoValue() { return true; }
};
