#include "stdafx.h"
#include "dab_header.h"

void llvm_dumpvaluetype(const char * ss,Value * v)
{
	std::string Q;
	llvm::raw_string_ostream ff1(Q);

	ff1 << "Value:\n" << *v << "\n\n";
	ff1 << "Type:\n" << *(v->getType()) << "\n\n";

	ff1.flush();
	
	qdtprintf2("Dump [%s]:\n%s", ss,Q.c_str());
}

bool qAssign::LLVM_build( llvm::Module * module )
{
	Value * ptr = 0;
	Value * v = 0;

	qString qL = L()->dumprawX();
	qString qR = R()->dumprawX();

	v = R()->BuildValue();

	if (!v)
	{
		qdterror("no R for assign");
	}

	ptr = L()->getLlvmVariable();

	if (ptr == 0)
	{
		qdterror("assign PTR = 0\n");
	}

	Builder.CreateStore(v, ptr, false);
	return false;
}

void qAssign::subupdateType()
{
	qString LL = L()->dumprawX();
	qString RR = R()->dumprawX();

	if (!(L()->neu_type)) return;
	if (L()->neu_type != R()->neu_type)
	{		
		qValue * cc = new qConvert(L()->neu_type, R(), "Assignment: ");
		replace_child(R(), cc);
	}
}

qString qAssign::print( int indent )
{
	return doIndent(indent) + "$" + L()->print() + " = " + R()->print() + std::string(indent?";":"");
}

qAssign::qAssign( qValue * var, qValue * value )
{
	insert(var);
	insert(value);
}
