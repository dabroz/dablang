#include "stdafx.h"
#include "dab_header.h"
#include "dab_internal.h"

void qUnOp::subupdateType()
{
	if (name == "not")
	{
		if (L()->neu_type != qneu_PrimitiveType::type_bool())
		{
			qValue * cc = new qConvert(qneu_PrimitiveType::type_bool(), L(), "Argument 1 of `not`: ");
			replace_child(L(), cc);
		}

		neu_type = qneu_PrimitiveType::type_bool();
		return;
	}
}

llvm::Value * qUnOp::BuildValue()
{
	if (name == "not")
	{
		return Builder.CreateNot(L()->BuildValue());
	}

	qdterror("unop 0");
	return 0;
}

qString qUnOp::print( int indent )
{
	qString s = L()->print(0);

	if (name == "not") return "!" + s;
	if (name == "neg") return "-" + s;

	return "???";
}

qUnOp::qUnOp( const char * _name, qValue * v )
{
	name = _name;
	insert(v);
}
