#include "stdafx.h"
#include "dab_header.h"

void CopyArgumentsToStack(dab_Function & fun)
{
	qSequence * args = (qSequence*)fun.node->L();
	qSequence * seq = (qSequence*)fun.node->R()->L();
	qSequence * newseq = new qSequence;
	for (int i = 0; i < args->size(); i++)
	{
		qDeclare * decl = (qDeclare*)(*args)[i];
		newseq->insert(new qDeclare(decl->neu_type, decl->name, new qFunctionArgument(fun.node, decl->name)));
	}	
	seq->remove_from_parent();
	qBlock * block = new qBlock(seq);
	newseq->insert(block);
	fun.node->R()->insert(newseq);
}
