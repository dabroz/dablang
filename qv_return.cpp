#include "qdt3.h"


bool qReturn::LLVM_build( llvm::Module * module )
{
	Builder.CreateRet(L()->BuildValue());
	return true;
}
