#pragma once

class qneu_ArrayType : public qneu_Type
{
public:
	qneu_Type * base;
	int size;

	virtual qString name() const ;
	virtual qString mangle() const ;

	virtual bool isPointer() const { return true; }

	virtual llvm::Type * llvm();

	virtual bool can_cast_to(qneu_Type * other) const;

	virtual qneu_Type * updateWithType( const qString & newname,qneu_Type * s );
public:
	static qneu_ArrayType * get(qneu_Type * basetype, qValue * size);
};
