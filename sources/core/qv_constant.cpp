#include "stdafx.h"
#include "dab_header.h"

llvm::Value * qConstant::BuildValue()
{
	qneu_PrimitiveType * pt = dynamic_cast<qneu_PrimitiveType*>(neu_type);

	if (pt->ptype == TYPE_INT32) return Lconstant(ivalue.x);
	if (pt->ptype == TYPE_FLOAT) return Lconstant(value.x);
	if (pt->ptype == TYPE_BOOL) return Lconstant(bvalue);

	qdterror("constant 0");
	return 0;
}

qConstant::qConstant( int vtype, int v )
{
	assert(vtype == TYPE_INT32);
	neu_type = qneu_PrimitiveType::type_int();
	ivalue.x = v;
}

qConstant::qConstant( int vtype, float v )
{
	assert(vtype == TYPE_FLOAT);
	neu_type = qneu_PrimitiveType::type_float();
	value.x = v;
}

qConstant::qConstant( int vtype, bool v )
{
	assert(vtype == TYPE_BOOL);
	neu_type = qneu_PrimitiveType::type_bool();
	bvalue = v;
}

qString qConstant::subdump()
{
	return print(0);
}

qString qConstant::print( int indent )
{
	char buffer[128];

	qneu_PrimitiveType * pt = dynamic_cast<qneu_PrimitiveType*>(neu_type);

	if (pt->ptype == TYPE_BOOL)
		sprintf(buffer, "%s", bvalue?"true":"false");

	if (pt->ptype == TYPE_INT32)
		sprintf(buffer, "%d", ivalue.x);

	if (pt->ptype == TYPE_FLOAT)
		sprintf(buffer, "%f", value.x);

	if (pt->ptype == TYPE_FLOAT4)
		sprintf(buffer, "[%f %f %f %f]", value.x, value.y, value.z, value.w);

	return doIndent(indent) + buffer;
}
