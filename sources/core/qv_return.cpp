#include "stdafx.h"
#include "dab_header.h"

bool qReturn::LLVM_build( llvm::Module * module )
{
	Builder.CreateRet(L()->BuildValue());
	return true;
}
