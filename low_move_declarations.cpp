#include "qdt3.h"

void movedcl2( qValue *  decl ) 
{
	qFunction * f = decl->function();

	qValue * fR    = f->R();
	qValue * fRL   = fR->L();
	qValue * fRLL  = fRL->L();

	if (!dynamic_cast<qStackalloc*>(fRLL))
	{
		fRL->children.insert(fRL->children.begin(), new qStackalloc);
		f->updateChildren();
		fRLL  = fRL->L();
	}

	qStackalloc * st = dynamic_cast<qStackalloc*>(fRLL);

	if (decl->is_parent(st)) return;

	if (decl->size())
	{
		qValue * asgnv = decl->L();
		decl->children.clear();

		qVariable * var = new qVariable(0);
		qDeclare * decl1 = (qDeclare*)decl;
		var->name = decl1->pretty_name;
		var->realname = decl1->real_name;
		var->neu_type = decl1->neu_type;

		qAssign * newass = new qAssign(var, asgnv);
		newass->loc = decl->loc;

		decl->replace_in_parent(newass);		

		newass->subupdateType();
	}
	else
	{
		qValue * olddec = decl;

		decl->remove_from_parent();
	}
	st->insert(decl);
}

void movedcl( qDeclare * decl ) 
{
	qProgram * prog = dynamic_cast<qProgram*>(decl->parent);
	if (prog) 
	{
		return;
	}
	qSequence * seq = dynamic_cast<qSequence*>(decl->parent);
	if (seq) 
	{
		qFunction * fun = dynamic_cast<qFunction*>(seq->parent);
		if (fun) 
		{
			return;
		}
	}
	movedcl2(decl);
}

void low_MoveDeclarations(qValue *  tree)
{
	tree->updateChildren();
	qDeclare * decl = dynamic_cast<qDeclare*>(tree);
	if (decl)
	{
		movedcl(decl);
		return;
	}
	qValueVec vvv = tree->children;
	for (int i = 0; i < vvv.size(); i++)
	{
		low_MoveDeclarations(vvv[i]);
	}
}
