#pragma once

class qNop : public qValue
{
public:
	qString print(int indent)
	{
		return "NOP";
	}
};
