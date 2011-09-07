#pragma once

class qneu_ArrayType : public dt_BaseType
{
public:
	dt_BaseType * base;
	int size;

	virtual qString name() const ;
	virtual qString mangle() const ;

	virtual bool isPointer() const { return true; }

	virtual llvm::Type * llvm();

	virtual bool can_cast_to(dt_BaseType * other) const;

	virtual dt_BaseType * updateWithType( const qString & newname,dt_BaseType * s );
public:
	static qneu_ArrayType * get(dt_BaseType * basetype, qValue * size);
};
