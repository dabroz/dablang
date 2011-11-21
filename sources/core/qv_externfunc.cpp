#include "stdafx.h"
#include "dab_header.h"
#include <windows.h>

extern ExecutionEngine *TheExecutionEngine ;

//#pragma pack (push)
//#pragma pack (1)
//struct JMPI
//{
//	unsigned char moveax;
//	unsigned addr;
//	unsigned char jmp;
//	unsigned char eax;
//};
//#pragma pack (pop)
//
//std::map<qString, Function *> glcalls;
//std::map<qString, JMPI *> glcalls2;
//
//void breakx()
//{
//	__asm { int 3 }
//}
//
//void LoadDeferredOpenGLFunctions();
//
//
//void LoadDeferredOpenGLFunctions()
//{
//	for (std::map<qString, Function *>::iterator it = glcalls.begin(), end = glcalls.end(); it != end; ++it)
//	{
//		Function * F = it->second;
//		const qString & fn = it->first;
//
//		HMODULE hm = LoadLibrary("opengl32.dll");
//		void * funp = GetProcAddress(hm, "wglGetProcAddress");
//
//		typedef  void * (__stdcall *procfun)(const char * n);
//
//		procfun getfun = (procfun)funp;
//
//		void * ff = getfun(fn.c_str());
//
//		qdtprintf2("LOAD OPENGL %08x %08x %08x <%s> \n", 
//			(unsigned)hm, (unsigned)getfun, (unsigned)ff, fn.c_str());
//
//		JMPI * pp = glcalls2[it->first];
//
//		pp->moveax = 0xB8;
//		pp->addr = (unsigned)ff;
//		pp->jmp = 0xFF;
//		pp->eax = 0xE0;
//	}
//}
//
//
//void * ExternForname(const qString & s, const qString & mn)
//{
//	std::map<qString, void *> funs;
//
//	funs["_f_printf_sv"] = (void*)qdtprintf2;
//	funs["_f_sprintf_pu1sv"] = sprintf;
////	funs["_f_load_gl_func_"] = LoadDeferredOpenGLFunctions;
////	funs["_f_breakx_"] = breakx;
//
//	if (funs.count(mn))
//	{
//		return funs[mn];
//	}
//
//	return 0;
//}

void qExternFunc::LLVM_prebuild( llvm::Module * module )
{
	Function * F = 0;
	bool winflag = false;
	qString winname;

	bool fromdll = false;
	qString dllname;
	qString dllfunname;
	//bool opengl = false;
	/*
	if ( _options.size())
	{*/
		int ee = _options.size();
		qString callcv = "";
		//qValueVec & vvvv = _options->children;
	
			if ( _options.count("win"))
			{
				winflag = true;
				winname =  _options["win"];
				if (dllfunname=="") dllfunname = name;
				callcv = "stdcall";

				F = llvm::Function::Create(GetType(),  llvm::Function::ExternalLinkage, dllfunname, module);
				InsertArgs(F);
				F->deleteBody();
			}
			if (_options.count("call"))
			{
				callcv = _options["call"];
			}
			if (_options.count("dll"))
			{
				dllname = _options["dll"];
				fromdll = true;
				if (dllfunname=="") dllfunname = name;
			}
			if (_options.count("name"))
			{
				dllfunname = _options["name"];
			}
			/*if (par == "opengl")
			{
				opengl = true;
				if (dllfunname=="") dllfunname = name;
			}*/
		
		if (winflag) //static import
		{

		}
		else
		{
			F = CreateFun(module);
		}
		/*if (opengl)
		{
			glcalls[dllfunname] = F;

			LPVOID funstub = VirtualAllocEx(GetCurrentProcess(), NULL, sizeof(JMPI), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

			glcalls2[dllfunname] = (JMPI*)funstub;

			TheExecutionEngine->addGlobalMapping(F, funstub);
		}*/

		if (_options.count("attrib"))
		{
			qString attrib = _options["attrib"];

			qString ccfuncname = "loader_" + attrib + "_cc";

			qGlobalVariable * val = the_module->_globals[ccfuncname];

			qString cc = val->children[0]->name; // todo: handle errors
		}

		if (callcv == "stdcall") F->setCallingConv(CallingConv::X86_StdCall);
		if (callcv == "cdecl") F->setCallingConv(CallingConv::C);
		F->setName(dllfunname);


		if (fromdll)
		{
			HMODULE hm = LoadLibrary(dllname.c_str());
			void * funp = GetProcAddress(hm, dllfunname.c_str());

			qdtprintf2("LOAD EXTERN %08x %08x <%s -> %s> \n", 
				(unsigned)hm, (unsigned)funp, dllname.c_str(), dllfunname.c_str());
			TheExecutionEngine->addGlobalMapping(F, funp);
		}
	/*}*/
	/*else
	{
		TheExecutionEngine->addGlobalMapping(F, ExternForname(name, this->func->mangled_name));
	}*/
	func->llvmd = F;
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

qExternFunc::qExternFunc( qValue * options, qValue * _type, qValue * _name, qValue * params, int shortversion )
{
	this->neu_type = _type->neu_type;
	this->name = _name->name;

	if (!params)
	{
		params = new qSequence();
	}

	if (shortversion)
	{
		_options["attrib"] = options->name;
	}
	else if (options)
	{
		if (options->size() % 2) { /* todo error */ }
		else
		{			
			for (int i = 0; i < options->size(); i+=2)
			{
				qString par = (*options)[i]->name;
				qString val = (*options)[i+1]->name;

				_options[par] = val;
			}
		}
	}

	insert(params);
}

bool qExternFunc::LLVM_build( llvm::Module * module )
{
	if (_options.count("attrib"))
	{
		the_module->AddLoader("loader_" + _options["attrib"], this, func->llvmd);
	}
	return false;
}
