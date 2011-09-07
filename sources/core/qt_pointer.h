#pragma once

class DABCORE_API qneu_PointerType : public dt_BaseType
{
public:
	virtual dt_BaseType * CreateConst() { return base->createConstPointer(); }

	dt_BaseType * base;
	virtual qString name() const { return base->name() + "*"; }
	virtual qString mangle() const { return "p" + base->mangle(); }
	static qneu_PointerType * get(dt_BaseType * basetype, bool ptrconst);

	virtual bool isPointer() const { return true; }

	virtual dt_BaseType * updateWithType( const qString & newname,dt_BaseType * s )
	{
		if (is_const) 
			return base->updateWithType(newname,s)->createConstPointer();
		else 
			return base->updateWithType(newname,s)->createPointer();
	}
	virtual llvm::Type * llvm();

	virtual bool can_cast_to(dt_BaseType * other) const;
private:
	qneu_PointerType(dt_BaseType * t, bool ptrconst) { base = t;  is_const = ptrconst; }
};
