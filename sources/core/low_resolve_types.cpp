#include "stdafx.h"
#include "dab_header.h"

void ResolveTypes( dab_Function & fun )
{
	fun.node->updateType();
}

void BuildFunctions( dab_Function & fun )
{
	fun.node->func = new qneu_Function(fun.node);
}