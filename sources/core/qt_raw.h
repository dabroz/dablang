#pragma once

class qneu_RawType : public qneu_Type
{
public:
	qString tname;
	qneu_RawType(qString t) : tname(t) {  };
	virtual qString name() const { return qString(is_const?"rawconst--":"")+ "{?"+tname+"?}"; }
	virtual bool isRaw() const { return true; }
	virtual qneu_Type * updateWithType(const qString & newname, qneu_Type * s );
	virtual Type * llvm () { qdterror("LLVM qneu_RawType!"); return 0; }
	virtual qneu_Type * CreateConst() { qneu_RawType * rr = new qneu_RawType(tname); rr->is_const = true; return rr; }
};