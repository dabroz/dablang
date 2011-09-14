#pragma once

class DABCORE_API qneu_RawType : public dt_BaseType
{
public:
	qString tname;
	qneu_RawType(qString t) : tname(t) {  };
	virtual qString name() const { return qString(is_const?"rawconst--":"")+ "{?"+tname+"?}"; }
	virtual bool isRaw() const { return true; }
	virtual dt_BaseType * updateWithType(const qString & newname, dt_BaseType * s );
	virtual llvm::Type * llvm () { qdterror("LLVM qneu_RawType!"); return 0; }
	virtual dt_BaseType * CreateConst() { qneu_RawType * rr = new qneu_RawType(tname); rr->is_const = true; return rr; }
	virtual qString rawname() const { return tname; }
};