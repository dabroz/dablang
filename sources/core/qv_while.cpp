#include "stdafx.h"
#include "dab_header.h"

bool qWhile::LLVM_build( llvm::Module * module )
{
	Function *TheFunction = Builder.GetInsertBlock()->getParent();

	BasicBlock * TestBB = BasicBlock::Create(getGlobalContext(), "while", TheFunction);

	BasicBlock * LoopBB = BasicBlock::Create(getGlobalContext(), "loop");
	BasicBlock * MergeBB = BasicBlock::Create(getGlobalContext(), "whilecont");

	Builder.CreateBr(TestBB);

	Builder.SetInsertPoint(TestBB);

	qValue * LL = L();
	qString LLS = LL->print();
	Builder.CreateCondBr(LL->BuildValue(), LoopBB, MergeBB);

	Builder.SetInsertPoint(LoopBB);
	TheFunction->getBasicBlockList().push_back(LoopBB);
	if (!children[1]->LLVM_build(module))
		Builder.CreateBr(TestBB);

	LoopBB = Builder.GetInsertBlock();

	Builder.SetInsertPoint(MergeBB);
	TheFunction->getBasicBlockList().push_back(MergeBB);
	MergeBB = Builder.GetInsertBlock();

	return false;
}

void qWhile::subupdateType()
{
	if (!L()) return;
	if (!L()->neu_type) return;

	if (L()->neu_type != qneu_PrimitiveType::type_bool())
	{
		qValue * cc = new qConvert(qneu_PrimitiveType::type_bool(), L(), "While condition: ");
		replace_child(L(), cc);
	}
}

qString qWhile::print( int indent )
{
	return doIndent(indent) + "while (" + children[0]->print() + ")\n" + children[1]->print(indent+(children[1]->isBlock()?0:1));
}

qWhile::qWhile( qValue * _condition, qValue * _repeat )
{
	insert(_condition);
	insert(_repeat);
}
