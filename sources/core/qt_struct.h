#pragma once

struct StructMember
{
	qneu_Type * type;
	qString name;

	int offset;
	int size;
};

class qneu_StructType : public qneu_Type
{
public:
	qneu_StructType * constver;

	std::vector<StructMember> members;
	qString stname;
	llvm::Type * cachetype;

	qneu_Type * GetTypeFor(qString membname) ;
	qneu_StructType() : cachetype(0) {}

	virtual qString name() const { return stname; }
	virtual qString mangle() const { char qq[128]; sprintf(qq,"S%d", stname.length()); return qq+stname; }
	bool isPrimitive() { return false; }
	virtual bool isStruct() const { return true; }

	virtual qneu_Type * CreateConst() { return constver; }

	virtual llvm::Type * llvm();
	virtual Value * getLllvVariable( qString name, Value * parent ) ;
};