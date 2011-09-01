#include "qdt3.h"

void qPointer::subupdateType()
{
	if (!L()) return;
	if (!L()->neu_type) return;
	neu_type = L()->neu_type->createPointer();
}

llvm::Value * qPointer::BuildValue()
{
	return L()->getLlvmVariable();
	
	qdterror("qpointer 0");
	return 0;
}
