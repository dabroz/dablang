#include "stdafx.h"
#include "dab_header.h"

qValue* qtree_program_start(qValue * v)
{
	qProgram * q = new qProgram();
	q->insert(v);
	return q;
}

qValue* qtree_program_append(qValue * seq, qValue * v)
{
	seq->insert(v);
	return seq;
}

qValue* qtree_seq_start(qValue * v)
{
	qSequence * q = new qSequence();
	q->insert(v);
	return q;
}

qValue* qtree_seq_append(qValue * seq, qValue * v)
{
	seq->insert(v);
	return seq;
}

qValue* qtree_declare_value(qValue* type, qValue* name, qValue * value)
{
	return new qDeclare(type, name, value);
}

qValue* qtree_declare(qValue* type, qValue* name)
{
	return qtree_declare_value(type, name, 0);
}

qValue* qtree_vararg()
{
	return qtree_declare_value(new qTypeHolder(qneu_VarargType::get()), 0, 0);
}

qValue* qtree_funcall(qValue * name, qValue * arglist)
{
	if (name->name == "min") return new qBinOp("min", (*arglist)[0], (*arglist)[1]);
	if (name->name == "max") return new qBinOp("max", (*arglist)[0], (*arglist)[1]);

	return new qFuncall(name, arglist);
}

qValue* qtree_binop(const char * op, qValue * left, qValue * right)
{
	return new qBinOp(op, left, right);
}

qValue* qtree_unop(const char * op, qValue * left)
{
	return new qUnOp(op, left);
}

qValue* qtree_constant_float(float value)
{
	return new qConstant(TYPE_FLOAT, value);
}

qValue* qtree_constant_int(int value)
{
	return new qConstant(TYPE_INT32, value);
}

qValue* qtree_id(const char * text)
{
	return new qIdentifier(text);
}

qValue* qtree_if(qValue* cond, qValue* _then, qValue* _else)
{
	return new qIf(cond, _then, _else);
}

qValue* qtree_function(qValue *type,qValue *id, qValue *arglist, qValue * body)
{
	return new qFunction(type, id, arglist, body);
}

qValue* qtree_return(qValue *v)
{
	return new qReturn(v);
}

qValue* qtree_block(qValue *v)
{
	return new qBlock(v);
}

qValue* qtree_assign(qValue *var, qValue*value)
{
	return new qAssign(var, value);
}

qValue* qtree_variable(qValue *v)
{
	return new qVariable(v);
}

qValue* qtree_subvariable(qValue *var, qValue * memb)
{
	return new qSubvariable(var, memb);
}

qValue* qtree_while(qValue * cond, qValue * code)
{
	return new qWhile(cond, code);
}

qValue* qtree_for(qValue * pre, qValue * test, qValue * post, qValue * code)
{
	return new qFor(pre, test, post, code);
}

qValue * qtree_struct(qValue * name, qValue * seq)
{
	return new qStruct(name, seq);
}

qValue * qtree_smember(qValue * type, qValue * name)
{
	return new qMember(type, name);
}

qValue* qtree_type(qValue * v)
{
	dt_BaseType * t = 0;
	if (v->name == "float") t = qneu_PrimitiveType::type_float();
	if (v->name == "float4") t = qneu_PrimitiveType::type_float4();
	if (v->name == "int") t = qneu_PrimitiveType::type_int();
	if (v->name == "bool") t = qneu_PrimitiveType::type_bool();

	if (v->name == "int8") t = qneu_PrimitiveType::type_int8();
	if (v->name == "int16") t = qneu_PrimitiveType::type_int16();
	if (v->name == "int32") t = qneu_PrimitiveType::type_int32();
	if (v->name == "int64") t = qneu_PrimitiveType::type_int64();
	if (v->name == "uint8") t = qneu_PrimitiveType::type_uint8();
	if (v->name == "uint16") t = qneu_PrimitiveType::type_uint16();
	if (v->name == "uint32") t = qneu_PrimitiveType::type_uint32();
	if (v->name == "uint64") t = qneu_PrimitiveType::type_uint64();
	
	if (v->name == "double") t = qneu_PrimitiveType::type_double();
	
	if (v->name == "byte") t = qneu_PrimitiveType::type_uint8();

	if (v->name == "void") t = qneu_VoidType::get();
	if (v->name == "cstring") t = qneu_CStringType::get();

	if (t==0)
	{
		dt_BaseType * TryAddStruct(qString & name);
		t = TryAddStruct(v->name);
		if (!t)
		{
			t = new qneu_RawType(v->name);
		}
		// should check typedefs too
	}
	return new qTypeHolder(t);
}

DABCORE_API qValue * QCODE(int pos, qValue *r)
{
	r->loc.cmp_pos = pos;
	return r;
}

DABCORE_API qValue * QCODEY(qValue * from, qValue * to)
{
	to->loc = from->loc;
	return to;
}
