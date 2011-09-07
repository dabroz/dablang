#pragma once

class qneu_PointerType : public qneu_Type
{
public:
	virtual qneu_Type * CreateConst() { return base->createConstPointer(); }

	qneu_Type * base;
	virtual qString name() const { return base->name() + "*"; }
	virtual qString mangle() const { return "p" + base->mangle(); }
	static qneu_PointerType * get(qneu_Type * basetype, bool ptrconst);

	virtual bool isPointer() const { return true; }

	virtual qneu_Type * updateWithType( const qString & newname,qneu_Type * s )
	{
		if (is_const) 
			return base->updateWithType(newname,s)->createConstPointer();
		else 
			return base->updateWithType(newname,s)->createPointer();
	}
	virtual llvm::Type * llvm();

	virtual bool can_cast_to(qneu_Type * other) const;
private:
	qneu_PointerType(qneu_Type * t, bool ptrconst) { base = t;  is_const = ptrconst; }
};
