#include "stdafx.h"
#include "dab_header.h"

bool qStackalloc::LLVM_build( llvm::Module * module )
{
	for (int i = 0; i < size(); i++)
	{
		qDeclare * v = dynamic_cast<qDeclare*>(children[i]);

		v->llvmvar = Builder.CreateAlloca(v->neu_type->llvm(), 0, v->pretty_name);
	}
	return false;
}
