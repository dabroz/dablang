#include "qdt3.h"

void add_ccc( qReturn * str ) 
{
	qFunction * f = str->function();

	if (f->neu_type != str->neu_type)
	{
		qValue * v = str->L();
		str->children.clear();

		str->insert(new qConvert(f->neu_type, v, "Return value: "));
		str->updateChildren();
	}
}

void low_FixReturnConverts(qValue * tree)
{
	qReturn * ret = dynamic_cast<qReturn*>(tree);
	if (ret)
	{
		add_ccc(ret);
		return;
	}
	for (int i = 0; i < tree->size(); i++)
	{
		low_FixReturnConverts((*tree)[i]);
	}
}

void low_CheckTypes(qValue * v)
{
	if (!v->IsNoValue() && dynamic_cast<qneu_RawType*>(v->neu_type))
	{
		char msg[2000];
		sprintf(msg, "Unknown type `%s`", v->neu_type->name().c_str());
		v->fireError(true, ERROR_TYPE_RAWTYPE, msg);
	}
	if (!v->IsNoValue() && v->neu_type == 0)
	{
		//char msg[2000];
		//sprintf(msg, "DEBUG Unknown type for %s", v->print().c_str());
		//v->fireError(true, ERROR_TYPE_ERROR, msg);
	}
	for (int i = 0; i < v->size(); i++)
	{
		low_CheckTypes((*v)[i]);
	}
}
