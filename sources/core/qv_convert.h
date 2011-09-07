#pragma once

class qConvert : public qValue
{
public:
	qConvert(dt_BaseType * type, qValue * val, const qString &extrainfo="");
	qString print(int indent);
	virtual llvm::Value * BuildValue() ;
};
