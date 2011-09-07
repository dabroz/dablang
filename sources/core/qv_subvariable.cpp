#include "stdafx.h"
#include "dab_header.h"
#include "dab_internal.h"

void qSubvariable::subupdateType()
{
	neu_type = 0;
	qneu_StructType * ss = dynamic_cast<qneu_StructType*>(L()->neu_type);
	if (ss)
	{
		neu_type = ss->GetTypeFor(name);
		if (!neu_type)	
		{
			fireError(true, ERROR_SUBVAR_DOESNTEXIST, "Type `" + ss->name() + "` has no member named `" + name + "`");
		}
	}
	else
	{
		if (L()->neu_type)
		{
			fireError(true, ERROR_SUBVAR_ERROR, "Cannot match subvariable `" + name + "` with type `" + L()->neu_type->name() + "`");
		}
		else
		{
			fireError(true, ERROR_SUBVAR_ERROR, "Cannot match subvariable `" + name + "`");
		}
	}
}

Value * qSubvariable::getLlvmVariable()
{
	Value * var = L()->getLlvmVariable();
	return L()->neu_type->getLllvVariable(name, var);
}

llvm::Value * qSubvariable::BuildValue()
{
	return Builder.CreateLoad(getLlvmVariable(), false, name);
}
