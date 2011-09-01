#include "qdt3.h"

static void updateref_internal( qVariable * var ) 
{
	qDeclare * decmatch = 0;
	for (int i = var->variablesavail.size() - 1; i >= 0; i--)
	{
		qDeclare * v = var->variablesavail[i];
		if (var->name == v->pretty_name)
		{
			decmatch = v;
			break;
		}
	}
	if (!decmatch)
	{
		qProgram * prog = dynamic_cast<qProgram*>(var->function()->parent);
		if (prog->globalvars.count(var->name))
		{
			decmatch = prog->globalvars[var->name];
		}
	}

	if (!decmatch)
	{
		char msg[9999];
		sprintf(msg,"Variable `%s` not found.", var->name.c_str());
		var->fireError(true, ERROR_VAR_NOT_FOUND, msg);
		return;
	}

	var->realname = decmatch->real_name;
	var->neu_type = decmatch->neu_type;
}

void low_UpdateVarReferences(qValue * q)
{
	qVariable * var = dynamic_cast<qVariable*>(q);
	if (var) updateref_internal(var);

	for (int i = 0; i < q->size(); i++)
	{
		low_UpdateVarReferences((*q)[i]);
	}
}
