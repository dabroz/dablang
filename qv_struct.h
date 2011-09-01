#pragma once

class qStruct : public qValue
{
public:
	qStruct(qValue * xname, qValue * xseq)
	{
		name = xname->name;
		insert(xseq);
	}
	virtual qString print(int indent = 0) { return "struct " + name + "\n{\n" + L()->print() + "}";	}
	virtual bool IsNoValue() { return true; }
};
