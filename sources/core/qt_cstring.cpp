#include "stdafx.h"
#include "dab_header.h"

llvm::Type * qneu_CStringType::llvm()
{
	return Type::getInt8PtrTy(getGlobalContext());
}
