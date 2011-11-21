#include "stdafx.h"
#include "dab_header.h"
#include "qt_void.h"

llvm::Type * qneu_VoidType::llvm()
{
	return llvm::Type::getVoidTy(llvm::getGlobalContext());
}
