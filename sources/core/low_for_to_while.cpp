#include "stdafx.h"
#include "dab_header.h"

static qValue * LowerPass_internal(qValue * v)
{
	if (v->children.size() != 4) return v;

	qValue * seq = qtree_seq_start(v->children[0]); // pre

	qValue * intcode = qtree_seq_start(v->children[3]);
	qtree_seq_append(intcode, v->children[2]);

	qValue * _while = qtree_while(v->children[1], qtree_block(intcode));
	qtree_seq_append(seq, _while);

	_while->subupdateType();

	return qtree_block(seq);
}


void low_ReplaceForWhile(qValue * program)
{
	for (int i = 0; i < program->size(); i++)
	{
		qValue * & q = program->children[i];
		if (qFor * _for = dynamic_cast<qFor*>(q))
		{
			q = LowerPass_internal(_for);
		}
		program->updateChildren();
		low_ReplaceForWhile(q);
		program->updateChildren();
	}
}
