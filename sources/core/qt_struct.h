#pragma once

struct DABCORE_API StructMember
{
	dt_BaseType * type;
	qString name;

	int offset;
	int size;
};

class DABCORE_API qneu_StructType : public dt_BaseType
{
public:
	qneu_StructType * constver;

	std::vector<StructMember> members;
	qString stname;
	llvm::Type * cachetype;

	dt_BaseType * GetTypeFor(qString membname) ;
	qneu_StructType() : cachetype(0) {}

	virtual qString name() const { return stname; }
	virtual qString mangle() const { char qq[128]; sprintf(qq,"S%d", stname.length()); return qq+stname; }
	bool isPrimitive() { return false; }
	virtual bool isStruct() const { return true; }

	virtual dt_BaseType * CreateConst() { return constver; }

	virtual llvm::Type * llvm();
	virtual llvm::Value * getLllvVariable( qString name, llvm::Value * parent ) ;
};