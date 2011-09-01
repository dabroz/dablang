#include "qdt3.h"

void qProgram::LLVM_prebuild( llvm::Module * module )
{
	for (int i =0 ;i<size();i++)
	{
		children[i]->LLVM_prebuild(module);
	}
}

bool qProgram::LLVM_build( llvm::Module * module )
{
	for (int i =0 ;i<size();i++)
	{
		extern bool UPDATING_JIT_CODE;
		if (UPDATING_JIT_CODE)
		{
			if (dynamic_cast<qDeclare*>(children[i]))
			{
				continue;
			}
		}
		
		children[i]->LLVM_build(module);
	}
	return false;
}

void qProgram::AppendProgram( qProgram * prog )
{
	for (int i = 0; i < prog->size(); i++)
	{
		this->insert((*prog)[i]);
	}
	for (std::map<qString, qDeclare*>::iterator it = prog->globalvars.begin(), end = prog->globalvars.end(); it != end; ++it)
	{
		globalvars[it->first] = it->second;
	}
}
