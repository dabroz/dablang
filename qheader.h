#pragma once

#include <map>

#include "llvmheader.h"
using namespace llvm;

extern Module * TheModule;

class qValue;
typedef std::string qString;
typedef std::vector<qValue*> qValueVec;
typedef qValueVec::iterator qValueIterator;

inline qString doIndent(int indent)
{
	qString r;
	for (int i = 0; i < indent; i++) r += "  ";
	return r;
}

typedef int int32_t;

struct FunctionArg
{
	qString name;
	class qneu_Type * type;

	llvm::Value * llvmreef;
};

class qneu_Function
{
public:
	qString mangle;
	qString mangled_name;

	qString name;
	class qneu_Type * returntype;
	std::vector<FunctionArg> args;

	qneu_Function(class qFunction * fun);

	Function * llvmd;
	bool isvararg() const ;
};

class qneu_Type
{
public:

	class qneu_PointerType * ptrtype;
	class qneu_PointerType * ptrconsttype;

	std::map<int, class qneu_ArrayType * > arraytypes;

	qneu_Type() : ptrtype(0),ptrconsttype(0),is_const(0) {};

	bool is_const;
	virtual bool isConst() const { return is_const; }
	virtual qneu_Type * CreateConst() { return 0; }

	virtual bool isPrimitive() const { return false; }
	virtual bool isStruct() const { return false; }
	virtual bool isPointer() const { return false; }
	virtual bool isVoid() const { return false; }
	virtual bool isRaw() const { return false; }
	virtual bool isVararg() const { return false; }
	virtual bool is_integer() const { return false; }

	virtual qString name() const { return "{??}"; }
	virtual qString mangle() const { return "?"; }

	virtual bool can_cast_to(qneu_Type * other) const { return false; }
	virtual const llvm::Type * llvm() = 0;
	virtual Value * getLllvVariable( qString name, Value * parent ) {return 0;}
	virtual qneu_Type * createPointer();
	virtual qneu_Type * createConstPointer();
	virtual qneu_Type * updateWithType( const qString & newname,class qneu_Type * s ) { return this; }
	virtual qneu_Type * CreateArray(qValue * size);
};

class qneu_ArrayType : public qneu_Type
{
public:
	qneu_Type * base;
	int size;

	virtual qString name() const ;
	virtual qString mangle() const ;

	virtual bool isPointer() const { return true; }

	virtual const llvm::Type * llvm();

	virtual bool can_cast_to(qneu_Type * other) const;

	virtual qneu_Type * updateWithType( const qString & newname,qneu_Type * s );
public:
	static qneu_ArrayType * get(qneu_Type * basetype, qValue * size);
};

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
	virtual const llvm::Type * llvm();

	virtual bool can_cast_to(qneu_Type * other) const;
private:
	qneu_PointerType(qneu_Type * t, bool ptrconst) { base = t;  is_const = ptrconst; }
};

inline qneu_Type * qneu_Type ::createPointer()
{
	return qneu_PointerType::get(this, false);
}

inline qneu_Type * qneu_Type ::createConstPointer()
{
	return qneu_PointerType::get(this, true);
}

class qneu_RawType : public qneu_Type
{
public:
	qString tname;
	qneu_RawType(qString t) : tname(t) {  };
	virtual qString name() const { return qString(is_const?"rawconst--":"")+ "{?"+tname+"?}"; }
	virtual bool isRaw() const { return true; }
	virtual qneu_Type * updateWithType(const qString & newname, qneu_Type * s );
	virtual const Type * llvm () { qdterror("LLVM qneu_RawType!"); return 0; }
	virtual qneu_Type * CreateConst() { qneu_RawType * rr = new qneu_RawType(tname); rr->is_const = true; return rr; }
};

class qneu_CStringType : public qneu_Type
{
public:
	virtual qneu_Type * CreateConst() { return this; }
	virtual qString name() const { return "cstring"; }
	virtual qString mangle() const { return "s"; }
	qneu_CStringType() {  }
	virtual const llvm::Type * llvm()
	{
		return Type::getInt8PtrTy(getGlobalContext());
	}
	virtual bool can_cast_to(qneu_Type * other) const 
	{
		if (other->isPointer()) return true;
		return false;
	}
	static qneu_CStringType * get() { static qneu_CStringType * ret = new qneu_CStringType(); ret->is_const = true; return ret; }
};

#define PRIMTYPE static qneu_PrimitiveType * ret = new qneu_PrimitiveType

class qneu_PrimitiveType : public qneu_Type
{
public:
	qneu_Type * constversion;

	int ptype;
	qString pname;
	qString pmangle;
	virtual qString name() const { return pname; }
	virtual bool isPrimitive() const { return true; }
	virtual qString mangle() const { return pmangle; }

	static qneu_PrimitiveType * type_int()    { return type_int32(); }

	virtual qneu_Type * CreateConst() { return constversion; }

	static qneu_PrimitiveType * consttype_double()  { PRIMTYPE(TYPE_DOUBLE,	"const_double", "Cl"); return ret; }
	static qneu_PrimitiveType * consttype_float()   { PRIMTYPE(TYPE_FLOAT,	"const_float", "Cf"); return ret; }
	static qneu_PrimitiveType * consttype_float4()  { PRIMTYPE(TYPE_FLOAT4,	"const_float4", "CF4"); return ret; }
	static qneu_PrimitiveType * consttype_bool()	{ PRIMTYPE(TYPE_BOOL,	"const_bool", "Cb"); return ret; }

	static qneu_PrimitiveType * type_double()  { PRIMTYPE(TYPE_DOUBLE,	"double", "l", consttype_double()); return ret; }
	static qneu_PrimitiveType * type_float()   { PRIMTYPE(TYPE_FLOAT,	"float", "f", consttype_float()); return ret; }
	static qneu_PrimitiveType * type_float4()  { PRIMTYPE(TYPE_FLOAT4,	"float4", "F4", consttype_float4()); return ret; }
	static qneu_PrimitiveType * type_bool()	   { PRIMTYPE(TYPE_BOOL,	"bool", "b", consttype_bool()); return ret; }

	static qneu_PrimitiveType * consttype_int8()    { PRIMTYPE(TYPE_INT8,	"const_int8",  "Ci1"); return ret; }
	static qneu_PrimitiveType * consttype_int16()   { PRIMTYPE(TYPE_INT16,	"const_int16", "Ci2"); return ret; }
	static qneu_PrimitiveType * consttype_int32()   { PRIMTYPE(TYPE_INT32,	"const_int32", "Ci4"); return ret; }
	static qneu_PrimitiveType * consttype_int64()   { PRIMTYPE(TYPE_INT64,	"const_int64", "Ci8"); return ret; }

	static qneu_PrimitiveType * consttype_uint8()   { PRIMTYPE(TYPE_UINT8,	"const_uint8",  "Cu1"); return ret; }
	static qneu_PrimitiveType * consttype_uint16()  { PRIMTYPE(TYPE_UINT16,	"const_uint16", "Cu2"); return ret; }
	static qneu_PrimitiveType * consttype_uint32()  { PRIMTYPE(TYPE_UINT32,	"const_uint32", "Cu4"); return ret; }
	static qneu_PrimitiveType * consttype_uint64()  { PRIMTYPE(TYPE_UINT64,	"const_uint64", "Cu8"); return ret; }

	static qneu_PrimitiveType * type_int8()    { PRIMTYPE(TYPE_INT8,	"int8",  "i1", consttype_int8()); return ret; }
	static qneu_PrimitiveType * type_int16()   { PRIMTYPE(TYPE_INT16,	"int16", "i2", consttype_int16()); return ret; }
	static qneu_PrimitiveType * type_int32()   { PRIMTYPE(TYPE_INT32,	"int32", "i4", consttype_int32()); return ret; }
	static qneu_PrimitiveType * type_int64()   { PRIMTYPE(TYPE_INT64,	"int64", "i8", consttype_int64()); return ret; }

	static qneu_PrimitiveType * type_uint8()   { PRIMTYPE(TYPE_UINT8,	"uint8",  "u1", consttype_uint8()); return ret; }
	static qneu_PrimitiveType * type_uint16()  { PRIMTYPE(TYPE_UINT16,	"uint16", "u2", consttype_uint16()); return ret; }
	static qneu_PrimitiveType * type_uint32()  { PRIMTYPE(TYPE_UINT32,	"uint32", "u4", consttype_uint32()); return ret; }
	static qneu_PrimitiveType * type_uint64()  { PRIMTYPE(TYPE_UINT64,	"uint64", "u8", consttype_uint64()); return ret; }

	virtual bool is_integer() const { return ptype >= TYPE_INT8 && ptype <= TYPE_UINT64; }

	virtual bool is_float() const { return ptype == TYPE_FLOAT || ptype == TYPE_DOUBLE; }
	virtual bool is_bool() const { return ptype == TYPE_BOOL; }

	virtual bool is_unsigned() const { return is_integer() && (ptype >= TYPE_UINT8 && ptype <= TYPE_UINT64); }
	virtual int ssize() const
	{
		switch(ptype)
		{
		case TYPE_BOOL: return 1;
			
		case TYPE_INT8:
		case TYPE_UINT8:
			return 8;

		case TYPE_INT16:
		case TYPE_UINT16:
			return 16;

		case TYPE_FLOAT:
		case TYPE_INT32:
		case TYPE_UINT32:
			return 32;

		case TYPE_INT64:
		case TYPE_UINT64:
		case TYPE_DOUBLE:
			return 64;

		case TYPE_FLOAT4:
			return 128;

		default:
			return -1;
		}
	}

	virtual bool can_cast_to(qneu_Type * other) const;

	virtual const llvm::Type * llvm();
private:
	qneu_PrimitiveType(int type, const char * xname, const char * xmangle, qneu_Type * constrv = 0)
	{
		ptype = type; pname = xname; pmangle = xmangle; constversion = constrv;
		if (!constrv) is_const = true;
	}
};
class qneu_VarargType : public qneu_Type
{
public:
	virtual qString name() const { return "vararg"; }
	virtual qString mangle() const { return "v"; }
	virtual bool isVararg() const { return true; }
	static qneu_VarargType * get() { static qneu_VarargType * ret = new qneu_VarargType; return ret; }

	virtual const Type * llvm() { qdterror("LLVM VARARG!"); return 0; }
private:
	qneu_VarargType() { }
};

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
	const llvm::Type * cachetype;

	qneu_Type * GetTypeFor(qString membname) ;
	qneu_StructType() : cachetype(0) {}

	virtual qString name() const { return stname; }
	virtual qString mangle() const { char qq[128]; sprintf(qq,"S%d", stname.length()); return qq+stname; }
	bool isPrimitive() { return false; }
	virtual bool isStruct() const { return true; }

	virtual qneu_Type * CreateConst() { return constver; }

	virtual const llvm::Type * llvm();
	virtual Value * getLllvVariable( qString name, Value * parent ) ;
};

class qneu_VoidType : public qneu_Type
{
public:
	qneu_VoidType() { }
	virtual bool isVoid() const { return true; }
	virtual qString name() const { return "void"; }
	virtual const llvm::Type * llvm();

	static qneu_VoidType * get() { static qneu_VoidType * ret = new qneu_VoidType(); return ret; }
};

struct QQLOC
{
	qString cmp_file;
	int cmp_pos;
	int cmp_line;
	int cmp_col;

	QQLOC() : cmp_file(""), cmp_pos(0), cmp_line(-1), cmp_col(-1) {};
};

class qValue
{
public:
	 QQLOC loc;

	virtual bool LLVM_build(llvm::Module * module) {return false;}

	virtual void LLVM_prebuild(llvm::Module * module) {}

	virtual llvm::Value * BuildValue() { return 0; }

	virtual Value * getLlvmVariable() { return 0; }

	bool remove_from_parent()
	{
		for (int i =0; i < parent->size(); i++)
		{
			if (parent->children[i]==this)
			{
				parent->children.erase(parent->children.begin() + i);
				parent->updateChildren();
				parent = 0;
				return true;
			}
		}
		return false;
	}

	bool replace_child(qValue * from, qValue * to)
	{
		for (int i =0; i < size(); i++)
		{
			if (children[i]==from)
			{
				from->parent = 0;
				children[i] = to;
				updateChildren();
				return true;
			}
		}
		return false;
	}

	bool replace_in_parent(qValue * newvalue)
	{
		for (int i =0; i < parent->size(); i++)
		{
			if (parent->children[i]==this)
			{
				parent->children[i] = newvalue;
				newvalue->parent = parent;
				parent->updateChildren();
				parent = 0;
				return true;
			}
		}
		return false;
	}

	qneu_Type * neu_type;
	qValue * parent;
	std::vector<class qDeclare*> variablesavail;
	struct { float x, y, z, w; } value;
	struct { int32_t x, y, z, w; } ivalue;
	bool bvalue;
	qString name;
	qValueVec children;

	bool is_parent(qValue * v)
	{
		if (this==v) return true;
		if (!parent) return false;
		return parent->is_parent(v);
	}

	qValue() : neu_type(0), parent((qValue*)0)
	{
		loc.cmp_pos=-1;
	};

	virtual ~qValue() {}

	void backtrace(int q = 0);
	void insert(qValue * v) { if (v) {children.push_back(v);  updateChildren();} }
	size_t size() const { return children.size(); }
	qValue * L() { if (size() < 1) return 0; return children[0]; }
	qValue * R() { if (size() < 2) return 0; return children[1]; }
	virtual qString print(int indent = 0) = 0;
	qValue* operator[](size_t i)
	{
		if (i >= size()) return 0;
		return children[i];
	}
	virtual bool isBlock() { return false; }
	virtual bool isInstruction() { return false; }
	virtual qString dump();
	virtual qString subdump() { return ""; }

	qString dumpraw();
	qString dumprawX();

	void updateChildren()
	{
		for (size_t i = 0, e = size(); i < e; i++)
		{
			children[i]->parent = this;
			children[i]->updateChildren();
		}
	}

	virtual void gatherVariables();

	void updateType()
	{
		for (size_t i = 0, e = size(); i < e; i++)
		{
			children[i]->updateType();
		}
		subupdateType();
	}

	virtual void subupdateType() { }

	class qFunction  * function();

	void fixPositions( const qString & file, const qString & str ) 
	{
		void getlinefrompos(const qString & text, int pos, int & line, int & col);

		loc.cmp_file = file;
		getlinefrompos(str, loc.cmp_pos, loc.cmp_line, loc.cmp_col);

		for (int i = 0; i < size(); i++)
		{
			children[i]->fixPositions(file, str);
		}
	}

	void fireError(bool error, int num, const qString & desc);

	void updateNewType( const qString & name, qneu_Type * s ) ;


	virtual bool IsNoValue() { return false; }


};

inline qString printType(qneu_Type * type)
{
	if (!type) return "###";
	return type->name();
}

qValue* qtree_program_start(qValue * v);
qValue* qtree_program_append(qValue * seq, qValue * v);
qValue* qtree_seq_start(qValue * v);
qValue* qtree_seq_append(qValue * seq, qValue * v);
qValue* qtree_declare_value(qValue* type, qValue* name, qValue * value);
qValue* qtree_declare(qValue* type, qValue* name);
qValue* qtree_funcall(qValue * name, qValue * arglist);
qValue* qtree_binop(const char * op, qValue * left, qValue * right);
qValue* qtree_unop(const char * op, qValue * left);
qValue* qtree_id(const char * text);
qValue* qtree_constant_float(float value);
qValue* qtree_constant_int(int value);
qValue* qtree_if(qValue* cond, qValue* _then, qValue* _else);
qValue* qtree_function(qValue *type,qValue *id, qValue *arglist, qValue * body);
qValue* qtree_return(qValue *v);
qValue* qtree_block(qValue *v);
qValue* qtree_assign(qValue *var, qValue*value);
qValue* qtree_variable(qValue *v);
qValue* qtree_subvariable(qValue *var, qValue * memb);
qValue* qtree_while(qValue * cond, qValue * code);
qValue* qtree_for(qValue * pre, qValue * test, qValue * post, qValue * code);
qValue* qtree_type(qValue * v);
qValue* qtree_struct(qValue * name, qValue * seq);
qValue* qtree_smember(qValue * type, qValue * name);
qValue* qtree_vararg();

extern IRBuilder<> Builder;
