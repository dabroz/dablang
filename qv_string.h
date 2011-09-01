#pragma once

class qStringConstant : public qValue
{
public:
	qStringConstant(const char * str);
	qString print(int indent)
	{
		qString vv = name;
		replace_all(vv, "\n", "\\n");
		replace_all(vv, "\r", "\\r");
		replace_all(vv, "\t", "\\t");
		return "\"" + vv + "\"";
	}
	virtual llvm::Value * BuildValue() ;
};
