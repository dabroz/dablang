#pragma once

class qConvert : public qValue
{
public:
	qConvert(qneu_Type * type, qValue * val, const qString &extrainfo="");
	qString print(int indent);
	virtual llvm::Value * BuildValue() ;
};
