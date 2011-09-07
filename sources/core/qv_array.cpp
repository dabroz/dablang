#include "stdafx.h"
#include "dab_header.h"

qString qArrayAccess::print( int indent /*= 0*/ )
{
	return L()->print() + "[" + R()->print() + "]";
}

void qArrayAccess::subupdateType()
{
	neu_type = 0;

	qneu_PointerType * ptype = dynamic_cast<qneu_PointerType*>(L()->neu_type);

	if (!ptype)
	{
		fireError(true, ERROR_TYPE_NO_POINTER, "Type `" + L()->neu_type->name() + "`is not a pointer type");
		return;
	}

	if (!R()->neu_type->is_integer())
	{
		qValue * cc = new qConvert(qneu_PrimitiveType::type_uint32(), R(), "Array index: ");
		replace_child(R(), cc);
	}
	
	neu_type = ptype->base;
}

qArrayAccess::qArrayAccess( qValue *var, qValue * index )
{
	insert(var);
	insert(index);
}

void llvm_dumpvaluetype(const char *, Value * v);

Value * qArrayAccess::getLlvmVariable()
{
	Value * v = L()->BuildValue();

	Value * ptr2 =  Builder.CreateGEP(v, R()->BuildValue());

	return ptr2;
}

llvm::Value * qArrayAccess::BuildValue()
{
	return Builder.CreateLoad(getLlvmVariable(), false, name);
}
