#include "qdt3.h"

bool qIf::LLVM_build( llvm::Module * module )
{
	Function *TheFunction = Builder.GetInsertBlock()->getParent();
			
	BasicBlock *ThenBB = BasicBlock::Create(getGlobalContext(), "then", TheFunction);
	BasicBlock *ElseBB = 0;
	if (size()==3)
		ElseBB = BasicBlock::Create(getGlobalContext(), "else");
	BasicBlock *MergeBB = BasicBlock::Create(getGlobalContext(), "ifcont");
			
	qValue * LL = L();
	Value * LLVAL = LL->BuildValue();
	Builder.CreateCondBr(LLVAL, ThenBB, ElseBB?ElseBB:MergeBB);

	Builder.SetInsertPoint(ThenBB);
	if (!children[1]->LLVM_build(module))
		Builder.CreateBr(MergeBB);
	
	ThenBB = Builder.GetInsertBlock();

	if (size()==3)
	{
		Builder.SetInsertPoint(ElseBB);
		TheFunction->getBasicBlockList().push_back(ElseBB);
		if (!children[2]->LLVM_build(module))
			Builder.CreateBr(MergeBB);

		ElseBB = Builder.GetInsertBlock();
	}

	Builder.SetInsertPoint(MergeBB);
	TheFunction->getBasicBlockList().push_back(MergeBB);
	
	return false;
}

void qIf::subupdateType()
{
	if (!L()) return;
	if (!L()->neu_type) return;

	if (L()->neu_type->mangle() != "b")
	{
		qValue * cc = new qConvert(qneu_PrimitiveType::type_bool(), L(), "If condition: ");
		replace_child(L(), cc);
	}
}

qString qIf::print( int indent )
{
	qString ret = doIndent(indent) + "if (" + children[0]->print() +")\n"+children[1]->print(indent+(children[1]->isBlock()?0:1));
	if (size()==3)
	{
		ret += "\n" + doIndent(indent) + "else\n";
		ret += children[2]->print(indent + (children[2]->isBlock()?0:1));
	}
	return ret;
}

qIf::qIf( qValue * _condition, qValue * _then, qValue * _else )
{
	insert(_condition);
	if (!_then) insert(new qSequence());
	else insert(_then);
	if (_else) insert(_else);
}
