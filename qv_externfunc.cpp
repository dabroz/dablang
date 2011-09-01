#include "qdt3.h"
#include <windows.h>

extern ExecutionEngine *TheExecutionEngine ;

#pragma pack (push)
#pragma pack (1)
struct JMPI
{
	unsigned char moveax;
	unsigned addr;
	unsigned char jmp;
	unsigned char eax;
};
#pragma pack (pop)

std::map<qString, Function *> glcalls;
std::map<qString, JMPI *> glcalls2;

void breakx()
{
	__asm { int 3 }
}

void LoadDeferredOpenGLFunctions()
{
	for (std::map<qString, Function *>::iterator it = glcalls.begin(), end = glcalls.end(); it != end; ++it)
	{
		Function * F = it->second;
		const qString & fn = it->first;

		HMODULE hm = LoadLibrary("opengl32.dll");
		void * funp = GetProcAddress(hm, "wglGetProcAddress");

		typedef  void * (__stdcall *procfun)(const char * n);

		procfun getfun = (procfun)funp;

		void * ff = getfun(fn.c_str());

		qdtprintf2("LOAD OPENGL %08x %08x %08x <%s> \n", 
			(unsigned)hm, (unsigned)getfun, (unsigned)ff, fn.c_str());

		JMPI * pp = glcalls2[it->first];

		pp->moveax = 0xB8;
		pp->addr = (unsigned)ff;
		pp->jmp = 0xFF;
		pp->eax = 0xE0;
	}
}

void * ExternForname(const qString & s, const qString & mn)
{
	std::map<qString, void *> funs;

	funs["_f_printf_sv"] = (void*)qdtprintf2;
	funs["_f_sprintf_pu1sv"] = sprintf;
	funs["_f_load_gl_func_"] = LoadDeferredOpenGLFunctions;
	funs["_f_breakx_"] = breakx;

	if (funs.count(mn))
	{
		return funs[mn];
	}

	return 0;
}

void qExternFunc::LLVM_prebuild( llvm::Module * module )
{
	Function * F = CreateFun(module);
	func->llvmd = F;

	bool fromdll = false;
	qString dllname;
	qString dllfunname;
	bool opengl = false;
	
	if (R())
	{
		int ee = R()->size();
		for (int i = 0; i < ee; i+=2)
		{
			qString par = R()->children[i]->name;
			qString val = R()->children[i+1]->name;

			if (par == "call")
			{
				if (val == "stdcall") F->setCallingConv(CallingConv::X86_StdCall);
				if (val == "cdecl") F->setCallingConv(CallingConv::C);
			}
			if (par == "dll")
			{
				dllname = val;
				fromdll = true;
				if (dllfunname=="") dllfunname = name;
			}
			if (par == "name" )
			{
				dllfunname = val;				
			}
			if (par == "opengl")
			{
				opengl = true;
				if (dllfunname=="") dllfunname = name;
			}
		}
		if (opengl)
		{
			glcalls[dllfunname] = F;

			LPVOID funstub = VirtualAllocEx(GetCurrentProcess(), NULL, sizeof(JMPI), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

			glcalls2[dllfunname] = (JMPI*)funstub;

			TheExecutionEngine->addGlobalMapping(F, funstub);
		}
		if (fromdll)
		{
			HMODULE hm = LoadLibrary(dllname.c_str());
			void * funp = GetProcAddress(hm, dllfunname.c_str());

			qdtprintf2("LOAD EXTERN %08x %08x <%s -> %s> \n", 
				(unsigned)hm, (unsigned)funp, dllname.c_str(), dllfunname.c_str());
			TheExecutionEngine->addGlobalMapping(F, funp);
		}
	}
	else
	{
		TheExecutionEngine->addGlobalMapping(F, ExternForname(name, this->func->mangled_name));
	}
}

qString qExternFunc::print( int indent )
{
	qString ret = "extern: " + printType(neu_type) + " " + name + "(";
	for (size_t i = 0, e = L()->size(); i < e; i++)
	{
		if (i) ret += ", ";
		ret += (*L())[i]->print(0);			
	}
	ret += ")";
	return ret;
}

qExternFunc::qExternFunc( qValue * options, qValue * _type, qValue * _name, qValue * params )
{
	this->neu_type = _type->neu_type;
	this->name = _name->name;

	if (!params)
	{
		params = new qSequence();
	}

	insert(params);
	if (options)
		insert(options);
}
