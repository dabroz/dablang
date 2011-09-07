#include "stdafx.h"
#include "dab_header.h"
#include "dab_internal.h"

llvm::Value * qStringConstant::BuildValue()
{
	int len = name.length() + 1;

	Type * t = ArrayType::get(Type::getInt8Ty(getGlobalContext()), len);

	Value * v = new GlobalVariable(*TheModule, t, true,GlobalVariable::InternalLinkage,
		ConstantArray::get(getGlobalContext(), StringRef(name), true),
		"cstr");

	return Builder.CreateBitCast(v, Type::getInt8PtrTy(getGlobalContext()), "cstrv");
}

qStringConstant::qStringConstant( const char * str )
{
	name = qString(str);
	name = name.substr(1, name.length() - 2);
	neu_type = qneu_CStringType::get();

	qString qq = "";
	for (int i = 0, e = name.length(); i < e; i++)
	{
		if (name[i] == '\\') 
		{
			char Q = name[++i];

			if (Q == 'n') qq += '\n';
			else if (Q == '\\') qq += '\\';
			else if (Q == '\r') qq += '\r';
			else{
				*(int*)0 = 0;
			}

		} else qq+=name[i];
	}
	name = qq;
}
