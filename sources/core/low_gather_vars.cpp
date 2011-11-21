#include "stdafx.h"
#include "dab_header.h"

void GatherVariables(dab_Function & fun)
{
	fun.node->gatherVariables();
}

static void updateref_internal( dab_Module * m, qVariable * var ) 
{
	for (std::vector<qDeclare*>::reverse_iterator it = var->variablesavail.rbegin(); it != var->variablesavail.rend(); ++it)
	{
		qDeclare * v = *it;
		if (var->name == v->pretty_name)
		{
			var->realname = v->real_name;
			var->neu_type = v->neu_type;
			return;
		}
	}

	if (m->_globals.count(var->name))
	{
		qGlobalVariable * gv = m->_globals[var->name];

		var->realname = gv->name;
		var->neu_type = gv->neu_type;
	}
	else
	{
		char msg[9999];
		sprintf(msg,"Variable `%s` not found.", var->name.c_str());
		var->fireError(true, ERROR_VAR_NOT_FOUND, msg);
	}
}

void low_UpdateVarReferences(dab_Module * m, qValue * q)
{
	qVariable * var = dynamic_cast<qVariable*>(q);
	if (var) updateref_internal(m, var);

	for (int i = 0; i < q->size(); i++)
	{
		low_UpdateVarReferences(m, (*q)[i]);
	}
}

void ResolveVariables(dab_Function & fun)
{
	low_UpdateVarReferences(fun.parent, fun.node);
}

void low_CleanupVariables(dab_Module * m, qValue * q)
{
	q->variablesavail.clear();
	for (int i = 0; i < q->size(); i++)
	{
		low_CleanupVariables(m, (*q)[i]);
	}
}

void CleanupVariables(dab_Function & fun)
{
	low_CleanupVariables(fun.parent, fun.node);
}
