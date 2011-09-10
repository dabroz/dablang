#pragma once

#ifdef DABCORE_EXPORTS
#define DABCORE_API __declspec(dllexport)
#else
#define DABCORE_API __declspec(dllimport)
#endif

class qValue;
typedef std::string qString;
typedef std::vector<qValue*> qValueVec;
typedef qValueVec::iterator qValueIterator;

bool ShouldWriteOutput();

DABCORE_API int qdtprintf(const char * format, ...);
DABCORE_API int qdtprintf2(const char * format, ...);
DABCORE_API void qdterror(const char * format, ...);

DABCORE_API void replace_all(std::string &str, const std::string &find_what, const std::string &replace_with);

enum
{
	TYPE_UNKNOWN,

	TYPE_VOID,
	TYPE_FLOAT,
	TYPE_FLOAT4,
	TYPE_BOOL,

	TYPE_INT8,
	TYPE_INT16,
	TYPE_INT32,
	TYPE_INT64,

	TYPE_UINT8,
	TYPE_UINT16,
	TYPE_UINT32,
	TYPE_UINT64,

	TYPE_DOUBLE,
};

struct DABCORE_API float4
{
	union
	{
		float x, y, z, w;
		float m[4];
	};
};

struct DABCORE_API qError
{
	int num;
	int error; // 1 error 0 warning
	qString desc;
	qString file;
	int line;
	int start;
	//int end;

	qError() { num = 0; error = 1; desc = "?"; file = "?"; line = 1; start = 1; }

	bool operator < (const qError & other)
	{
		if (file != other.file) return file < other.file;
		if (line != other.line) return line < other.line;
		return start < other.start;
	}
};

struct DABCORE_API parse_parm
{
	void			*yyscanner;
	char			*buf;
	int				pos;
	int				length;
	class qValue	*result;
	class dab_Module		*module;

	std::string filename;
	int errorsfound;
	std::vector<qError> errors;
};

void dab_Parse(char *buf, qValue **result, const std::string & filename, std::vector<qError> & errors, class dab_Module * module);

#define YYSTYPE         qValue*
#define YY_EXTRA_TYPE   parse_parm *

int     yylex(YYSTYPE *, void *);
int     yylex_init(void **);
int     yylex_destroy(void *);
void    yyset_extra(YY_EXTRA_TYPE, void *);
int     yyparse(parse_parm *, void *);
void    yyerror(parse_parm *parm,void*scanner,const char*msg);

#define YYDEBUG 1

DABCORE_API qValue * QCODE(int pos, qValue *r);
DABCORE_API qValue * QCODEY(qValue * from, qValue * to);

enum 
{
	ERROR_SYNTAX_ERROR					= 1,
	ERROR_FUNCTION_DOESNT_EXIST			= 2,
	ERROR_NO_MATCHING_CALL				= 3,
	ERROR_STRUCT_EXISTS					= 4,
	ERROR_SUBVAR_ERROR					= 5,
	ERROR_SUBVAR_DOESNTEXIST			= 6,
	WARNI_IMPLICIT_CONVERT				= 7,
	ERROR_VAR_NOT_FOUND					= 8,
	ERROR_TYPE_ERROR					= 9,
	ERROR_NO_BINOP						= 10,
	ERROR_TYPE_NO_POINTER				= 11,
	ERROR_TYPE_RAWTYPE					= 12,

	MAX_ERROR_NUM
};

extern llvm::Module * TheModule;

inline qString doIndent(int indent)
{
	qString r;
	for (int i = 0; i < indent; i++) r += "  ";
	return r;
}

typedef int int32_t;

struct DABCORE_API FunctionArg
{
	qString name;
	class dt_BaseType * type;

	llvm::Value * llvmreef;
};

class DABCORE_API qneu_Function
{
public:
	qString mangle;
	qString mangled_name;

	qString name;
	class dt_BaseType * returntype;
	std::vector<FunctionArg> args;

	qneu_Function(class qFunction * fun);

	llvm::Function * llvmd;
	bool isvararg() const ;
};

class DABCORE_API dt_BaseType
{
public:

	class qneu_PointerType * ptrtype;
	class qneu_PointerType * ptrconsttype;

	std::map<int, class qneu_ArrayType * > arraytypes;

	dt_BaseType() : ptrtype(0),ptrconsttype(0),is_const(0) {};

	bool is_const;
	virtual bool isConst() const { return is_const; }
	virtual dt_BaseType * CreateConst() { return 0; }

	virtual bool isPrimitive() const { return false; }
	virtual bool isStruct() const { return false; }
	virtual bool isPointer() const { return false; }
	virtual bool isVoid() const { return false; }
	virtual bool isRaw() const { return false; }
	virtual bool isVararg() const { return false; }
	virtual bool is_integer() const { return false; }

	virtual qString name() const { return "{??}"; }
	virtual qString mangle() const { return "?"; }

	virtual bool can_cast_to(dt_BaseType * other) const { return false; }
	virtual llvm::Type * llvm() = 0;
	virtual llvm::Value * getLllvVariable( qString name, llvm::Value * parent );
	virtual dt_BaseType * createPointer();
	virtual dt_BaseType * createConstPointer();
	virtual dt_BaseType * updateWithType( const qString & newname,class dt_BaseType * s ) { return this; }
	virtual dt_BaseType * CreateArray(qValue * size);
};

#include "qt_array.h"
#include "qt_pointer.h"
#include "qt_raw.h"
#include "qt_primitive.h"
#include "qt_vararg.h"
#include "qt_struct.h"
#include "qt_cstring.h"
#include "qt_void.h"

struct DABCORE_API QQLOC
{
	qString cmp_file;
	int cmp_pos;
	int cmp_line;
	int cmp_col;

	QQLOC() : cmp_file(""), cmp_pos(0), cmp_line(-1), cmp_col(-1) {};
};

class DABCORE_API qValue
{
public:
	 QQLOC loc;

	 std::string originFile;

	virtual bool LLVM_build(llvm::Module * module) {return false;}

	virtual void LLVM_prebuild(llvm::Module * module) {}

	virtual llvm::Value * BuildValue() { return 0; }

	virtual llvm::Value * getLlvmVariable() { return 0; }

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

	dt_BaseType * neu_type;
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

	void updateNewType( const qString & name, dt_BaseType * s ) ;


	virtual bool IsNoValue() { return false; }


};

inline qString printType(dt_BaseType * type)
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
qValue* qtree_type(dab_Module * module, qValue * v);
qValue* qtree_struct(qValue * name, qValue * seq);
qValue* qtree_smember(qValue * type, qValue * name);
qValue* qtree_vararg();
qValue* qtree_globalvar(qValue * type, qValue * name, qValue * value);

void debugqv(const char * name, ...);

#define DEBUGQ(...) debugqv(__FUNCTION__, ##__VA_ARGS__,0)

qString binSym(const qString &name);
//qValue* qtree_type(qValue * v);

void low_ReplaceForWhile(qValue * program);
void low_UpdateVarReferences(qValue * q);
//void low_GetStructs(qValue * tree);
void low_FixReturnConverts(qValue * tree);
void low_MoveDeclarations(qValue * tree);
void low_FindFunctions(qValue * pro);
void low_CheckTypes(qValue * v);

qString  RunLLVMBuilding(qValue * prog);

llvm::Value * Lconstant(int v);
llvm::Value * Lconstant(float v);
llvm::Value * Lconstant(bool v);

#include "qv_instruction.h"
#include "qv_constant.h"
#include "qv_assign.h"
#include "qv_block.h"
#include "qv_constant.h"
#include "qv_sequence.h"
#include "qv_funcall.h"
#include "qv_if.h"
#include "qv_while.h"
#include "qv_binop.h"
#include "qv_identifier.h"
#include "qv_return.h"
#include "qv_for.h"
#include "qv_program.h"
#include "qv_declare.h"
#include "qv_function.h"
#include "qv_struct.h"
#include "qv_member.h"
#include "qv_typeholder.h"
#include "qv_variable.h"
#include "qv_subvariable.h"
#include "qv_convert.h"
#include "qv_nop.h"
#include "qv_stackalloc.h"
#include "qv_externfunc.h"
#include "qv_string.h"
#include "qv_break.h"
#include "qv_pointer.h"
#include "qv_unop.h"
#include "qv_dereference.h"
#include "qv_typedef.h"
#include "qv_array.h"
#include "qv_globalvar.h"

// DLL interface

struct DABCORE_API dab_Function
{
	qFunction * node;
	bool dirty;

	dab_Function() : node(0), dirty(false) {};
	dab_Function(qFunction * f) : node(f), dirty(true) {};
};

struct DABCORE_API dab_Struct
{
	qStruct * node;
	bool dirty;
	qneu_StructType * type;

	dab_Struct() : node(0), dirty(false), type(0) {};
	dab_Struct(qStruct * s) : node(s), dirty(true) {};
};

struct DABCORE_API dab_Typedef
{
	qTypedef * node;
	bool dirty;

	dab_Typedef() : node(0), dirty(false) {};
	dab_Typedef(qTypedef * t) : node(t), dirty(true) {};
};

class DABCORE_API dab_Module
{
public:
	std::map<std::string, qGlobalVariable*> _globals;
	std::map<std::string, dab_Typedef> _typedefs;
	std::map<std::string, dab_Struct> _structs;
	std::map<std::string, dab_Function> _functions;

	std::vector<qError> _errors;

	void Append(qValue * program);
	void ProcessTypes();
	dt_BaseType * ResolveType(const std::string & name);
};

DABCORE_API dab_Module * dab_CompileFiles(std::map<qString, qString> & files, dab_Module * origin);
