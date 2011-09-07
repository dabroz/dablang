#include "stdafx.h"
#include "dab_header.h"
#include "dab_internal.h"

void qDereference::subupdateType()
{
	if (!L()) return;
	if (!L()->neu_type) return;
	qneu_PointerType* pt = dynamic_cast<qneu_PointerType*> (L()->neu_type);
	if (pt)
	{
		neu_type = pt->base;
	}
}

llvm::Value * qDereference::BuildValue()
{
	return Builder.CreateLoad(getLlvmVariable());
	return 0;
}

Value * qDereference::getLlvmVariable()
{
	return L()->BuildValue();
}

qString qDereference::print( int indent )
{
	return "*(" + L()->print() + ")";
}
