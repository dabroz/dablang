#include "stdafx.h"
#include "dab_header.h"
#include "dab_internal.h"

bool produce_output = true;

bool ShouldWriteOutput() { return produce_output; }

int bisonfprintf(FILE * file, const char * format, ...)
{
	va_list args;
	va_start (args, format);
	int q = vfprintf (file, format, args);
	va_end (args);
	return q;
}

int atoix(const char *ss)
{
	int ret = 0;
	if (1==sscanf(ss, "%x", &ret)) 
	{
		return ret;
	}
	return 0;
}

size_t lexlexfwrite(const void *buffer,size_t size,size_t count,FILE *stream )
{
	const char*qq=(const char*)buffer;
	return fwrite(buffer, size,count,stream);
}

void getlinefrompos(const qString & text, int pos, int & line, int & col)
{
	if (pos==-1) { line = -1; col = -1; }
	int i1 = -100;
	int i2 = 0;
	int iq = 0;
	int lnn = 0;
	while (true)
	{
		if (iq==text.length() || text[iq]=='\n')
		{
			lnn++; i1 = i2; i2 = iq;
			if (iq>pos-1) break;
		}
		iq++;
	}

	line = lnn;
	col =  pos - i1;
}

void yyerror(parse_parm *parm,void*scanner,const char*msg)
{
	parm->errorsfound++;

	const char * buf = q_yy_buf(scanner);
	size_t pos = q_yy_pos(scanner);
	size_t len = strlen(buf);

	size_t left = pos, right = pos;

	if (left > 0) left--;

	while (left > 0 && buf[left] != '\n') left--;
	while (right < len && buf[right] != '\n') right++;

	if (left == 0) left = -1;

	string line(buf+left+1,right-left-1);

	int lnn, cll;
	getlinefrompos(buf, pos, lnn, cll);
	qError err;
	err.error = 1;
	err.num = ERROR_SYNTAX_ERROR;
	err.file = parm->filename;
	err.line = lnn;
	err.start =cll;
	err.desc = msg;
	parm->errors.push_back(err);

	qdtprintf("---------\nerror: %s\n", msg);
	qdtprintf("line : %s\n", line.c_str());
	qdtprintf("       ");
	for (size_t i = 0; i < pos-left-2; i++) qdtprintf(" ");
	qdtprintf("^\n\n");
}

std::string getFile(const char * name)
{
	FILE * f = fopen(name, "rb");
	fseek(f, 0, SEEK_END);
	long q = ftell(f);
	fseek(f, 0, SEEK_SET);

	char * dat = (char*)malloc(q+1);
	fread(dat, 1, q, f);
	fclose(f);
	dat[q] = 0;

	std::string ret = dat;
	free(dat);

	return ret;
}

DABCORE_API void setFile(const char *name, const qString&body)
{
	FILE * f = fopen(name, "wb");
	fwrite(body.c_str(), 1, body.length(), f);
	fclose(f);
}

qString ENEN(qString s)
{
	qString q;
	for (int i = 0;i<s.length();i++)
	{
		if (s[i]=='<') q+="&lt;";
		else if (s[i]=='>') q+="&gt;";
		else q+=s[i];
	}
	return q;
}

void ResetFunctions();
void ResetStruct();

bool runCode(qValue * prog)
{
	qString  qww = RunLLVMBuilding(prog);
	return true;
}
/*
void run_passes(qValue * v, bool nostructures=false)
{
	//if (!nostructures) low_GetStructs(v);
	low_FindFunctions(v);

	low_ReplaceForWhile(v);
	v->gatherVariables();
	//low_UpdateVarReferences(v);
	v->updateType();
	low_FixReturnConverts(v);
}
*/
qValue * updateCode = 0;
qValue * originalCode = 0;

void AddDablangStatus(const qString & ss)
{
	// PLACEHOLDER
}

bool UPDATING_JIT_CODE = false;

qValue * update_funcs()
{
	for (int i = 0; i < updateCode->size(); i++)
	{
		qFunction * f = dynamic_cast<qFunction*>(updateCode->children[i]);
		if (f)
		{
			char msg[2000];
			sprintf(msg, "Updating function `%s`", f->name.c_str());
			f->LLVM_update();
		}
	}
	return updateCode;
}
//
//bool subupdatecompiled(const char *txt, qValue * last)
//{
//	UPDATING_JIT_CODE  = true;
//	originalCode =last;
//	//ERRORS_FOUND = 0;
//
//	qValue * ret = 0;
//	//currentFile = "__virtual_update.dab";
//	std::vector<qError> errors;
//	dab_Parse((char*)txt, &ret, "__virtual_update.dab", errors, 0);
//
//	if (errors.size()) return false;
//
//	ret->updateChildren();
//	ret->fixPositions("__virtual_update.dab", txt);
//
//	for (int i = 0 ;i<ret->size();i++)
//	{
//		if (dynamic_cast<qDeclare*>(ret->children[i]))
//		{
//			ret->children[i]->remove_from_parent();
//			i--;
//		}
//	}
//
//	qProgram * prog0 = (qProgram*)originalCode;
//	qProgram * prog1 = (qProgram*)ret;
///*
//	for (std::map<qString, qDeclare*>::iterator it = prog0->globalvars.begin(), end = prog0->globalvars.end(); it != end; ++it)
//	{
//		prog1->globalvars[it->first] = it->second;
//	}
//*/
//	run_passes(ret,true);
//	low_MoveDeclarations(ret);
//	low_CheckTypes(ret);
//
//	updateCode = ret;
//
//	if (ShouldWriteOutput()) 
//		setFile("UPDATE.html", "<ul>" + ret->dumpraw() + "</ul>");
//
//	return true;
//}


void dab_Module::ProcessFunctions( procfun fun )
{
	for (it_f it = _functions.begin(), end = _functions.end(); it != end; ++it)
	{
		for (unsigned i = 0; i < it->second.size(); i++)
			fun(it->second[i]);
	}
}

void dab_Module::ProcessVariables( procvar fun )
{
	for (it_g it = _globals.begin(), end = _globals.end(); it != end; ++it)
	{
		fun(it->second);
	}
}

llvm::Module * g_Module = 0;

llvm::Module * CreateModule();

void qValue::error( const char * format, ... )
{
	char data[16 * 1024];
	sprintf(data, "[%s (%s)] error: %s\n", print(0).c_str(), dumprawX().c_str(), format);
	va_list arg;
	va_start(arg, format);
	qdterrorv(data, arg);
	va_end(arg);
}

void BuildFunction(dab_Function & fun)
{
	qdtprintf("Building function <%s>\n", fun.node->name.c_str());
	//fun.node->LLVM_prebuild(g_Module);
	fun.node->LLVM_build(g_Module);
}

void BuildVariable(qGlobalVariable *var)
{
	qdtprintf("Building var <%s>\n", var->name.c_str());
	var->LLVM_build(g_Module);
}

void PreBuildFunction(dab_Function & fun)
{
	qdtprintf("Prebuilding function <%s>\n", fun.node->name.c_str());
	fun.node->LLVM_prebuild(g_Module);
	//fun.node->LLVM_build(g_Module);
}

struct qINI
{
	std::map<qString, qString> params;
};

qINI g_INI;

void ReadIniConfig()
{
	qString s = getFile("dab.ini") + "\n";
	char line[1024];
	int p = 0;
	qString sector;
	for (int i = 0, l = s.length(); i < l; i++)
	{
		if (s[i] == '\r') continue;
		if (s[i] == '\n')
		{
			if (!p) continue;
			line[p] = 0;
			if (line[0] == '[')
			{
				sector = qString(line + 1, p - 2);
				
			}
			else if (line[0] == '#')
			{
				
			}
			else
			{
				const char * eq = strstr(line, "=");
				if (eq)
				{
					qString key = sector + "/" + qString(line, eq - line);
					qString value = eq + 1;
					g_INI.params[key] = value;
				}
				else
				{}
			}

			p = 0;
		}
		else line[p++] = s[i];
	}
}
#include <windows.h>

void win32_run(const char * exe, const char * cmdline)
{
	qdtprintf("run: `%s %s`\n", exe, cmdline);

	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	memset(&pi, 0, sizeof(pi));
	memset(&si, 0, sizeof(si));
	si.cb = sizeof(si);

	HANDLE pipew, piper;
	BOOL res;

	SECURITY_ATTRIBUTES saAttr; 

	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES); 
	saAttr.bInheritHandle = TRUE; 
	saAttr.lpSecurityDescriptor = NULL; 

	res = CreatePipe(&piper, &pipew, &saAttr, 0);
	assert(res);

	SetHandleInformation(piper, HANDLE_FLAG_INHERIT, 0);

	si.hStdOutput = pipew;
	si.hStdError = pipew;
	si.dwFlags |= STARTF_USESTDHANDLES;
	char p[1024*16];
	sprintf(p,"%s %s", exe, cmdline);
	res = CreateProcess(0, p, 0, 0, 1, NORMAL_PRIORITY_CLASS, 0, 0, &si, &pi);
	
	if (res == 0)
	{
		qdtprintf("`%s %s` failed\n", exe, cmdline);
	}
	else
	{
		WaitForSingleObject(pi.hProcess, INFINITE);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}

	CloseHandle(pipew);
	char p2[16 * 1024];
	DWORD p3 = 666;
	res = ReadFile(piper, p2, 16 * 1024, &p3, 0);
	p2[p3]=0;
	qdtprintf("%d: %s\n", p3, p3?p2:"nope");
	CloseHandle(piper);
}

void temp_compileToExe(const qString & s)
{
	ReadIniConfig();

	setFile("__build.ll", s);
	//win32_run(g_INI.params["tools/llvmas"].c_str(), "--help");
	win32_run(g_INI.params["tools/llvmas"].c_str(), "__build.ll");
	win32_run(g_INI.params["tools/llvmopt"].c_str(), "-O3 -S __build.bc -o __build.opt.ll");
	win32_run(g_INI.params["tools/llvmas"].c_str(), "__build.opt.ll");
	win32_run(g_INI.params["tools/llvmllc"].c_str(), "__build.opt.bc");
	win32_run(g_INI.params["tools/as"].c_str(), "__build.opt.s -o __build.o");
	qString xx = "\"" + g_INI.params["lib/win"] + "user32.lib\"";
	win32_run(g_INI.params["tools/ld"].c_str(), ("--subsystem windows -e __f_main_  -o __build.exe __build.o " + xx).c_str());
}

void dab_Module::AddLoader( const qString & loader, qExternFunc* fun, Function * F ) 
{
	BasicBlock *BB = BasicBlock::Create(getGlobalContext(), fun->name, preloader);
	Builder.SetInsertPoint(BB);

	Builder.CreateCast(Instruction::CastOps::BitCast, F, qneu_PrimitiveType::consttype_uint8()->createPointer()->llvm(), "xxx");


	std::string Q=PrintModule();

	setFile("compile_llvm.txt",Q);
}

void dab_Module::BuildCode()
{
	preloader = 0;

	if (g_Module) { delete g_Module; g_Module = 0; }
	//if (!g_Module)
	{
		g_Module = CreateModule();
	}

	std::vector<Type *> x;
	preloader = Function::Create(FunctionType::get(llvm::Type::getVoidTy(llvm::getGlobalContext()), x, false), llvm::Function::ExternalLinkage, "!dab_init", g_Module);

	ProcessVariables(BuildVariable);
	ProcessFunctions(PreBuildFunction);
	ProcessFunctions(BuildFunction);

	if (ShouldWriteOutput())
	{
		std::string Q=PrintModule();

		setFile("compile_llvm.txt",Q);

		temp_compileToExe(Q);
	}
}

qString dab_Module::PrintModule()
{
	qString Q;
	std::string ErrorInfo;
	llvm::raw_string_ostream * ff1 = new llvm::raw_string_ostream(Q);
	llvm::AssemblyAnnotationWriter * Annotator = 0;
	g_Module->print(*ff1, Annotator);
	return Q;
}

void MoveVarsToStack(dab_Function & fun)
{
	low_MoveDeclarations(fun.node);
}

DABCORE_API dab_Module * dab_CompileFiles(std::map<qString, qString> & files, dab_Module * module)
{
	setlocale(LC_ALL,"C");
	if (module) { delete module; module = 0; }
	if (!module) module = new dab_Module;
	if (files.size() == 0) return module;

	bool success = true;
	module->_errors.clear();

	for (std::map<qString, qString>::iterator it = files.begin(), end = files.end(); it != end; ++it)
	{
		int errorcount = module->_errors.size();
		qValue * ret = 0;
		dab_Parse((char*)it->second.c_str(), &ret, it->first, module->_errors, module);
		
		if (module->_errors.size() - errorcount) success = false;
		else
		{
			ret->fixPositions(it->first, it->second, module);
			low_ReplaceForWhile(ret);
			module->Append(ret);
		}
	}

	if (ShouldWriteOutput()) 
		setFile("x2_compile.html", module->Dump());

	module->ProcessTypes();
	
	module->ProcessFunctions(CopyArgumentsToStack);
	module->ProcessFunctions(GatherVariables);
	module->ProcessFunctions(ResolveVariables);
	module->ProcessFunctions(CleanupVariables);
	module->ProcessFunctions(BuildFunctions);
	module->ProcessFunctions(ResolveTypes);
	module->ProcessFunctions(MoveVarsToStack);

	/*
	v->gatherVariables();
	low_UpdateVarReferences(v);
	v->updateType();
	low_FixReturnConverts(v);*/

	if (ShouldWriteOutput()) 
		setFile("x3_compile.html", module->Dump());

	module->BuildCode();

	return module;
}

dt_BaseType * dab_Module::ResolveType( const std::string & name )
{
	return 0;
}

void dab_Module::ProcessTypes()
{
	for (std::map<std::string, dab_Typedef>::iterator it = _typedefs.begin(), end = _typedefs.end(); it != end; ++it)
	{
		if (it->second.dirty)
		{
			di_NotifyAboutType(it->first, it->second.node->neu_type, this);
			it->second.dirty = false;
		}
	}
	for (std::map<std::string, dab_Struct>::iterator it = _structs.begin(), end = _structs.end(); it != end; ++it)
	{
		if (it->second.dirty)
		{
			it->second.type = di_CreateStruct(it->second.node, this);
			di_NotifyAboutType(it->first, it->second.type, this);
			it->second.dirty = false;
		}
	}
}

void dab_Module::Append( qValue * program )
{
	// TODO: remove all old program->filename objects from module

	// TODO: update only symbols that changed!

	for (int i = 0; i < program->size(); i++)
	{
		qValue * v = (*program)[i];

		if (qGlobalVariable * d = dynamic_cast<qGlobalVariable*>(v))
		{
			_globals[d->name] = d;
		}
		else if (qTypedef * t = dynamic_cast<qTypedef*>(v))
		{
			_typedefs[t->name] = t;
		}
		else if (qStruct * s = dynamic_cast<qStruct*>(v))
		{
			_structs[s->name] = s;
		}
		else if (qFunction * f = dynamic_cast<qFunction*>(v))
		{
			dab_Function ff = f;
			ff.parent = this;
			_functions[f->name].push_back(ff);
		}
	}

	// TODO: handle removed objects (a.dab: int a; int b; b.dab: int foo() { return a; }
	// If you remove `int a` from a.dab, `foo` in b.dab needs to be recompiled and user
	// must receive an error
	//
	// Solution: global objects should store their users?
}

/*
qValue * compileText(std::map<qString, qString> & filemap)
{
	setlocale(LC_ALL,"C");

	if (filemap.size() == 0) return 0;

//	ERRORS_FOUND = 0;
	ResetFunctions();
	ResetStruct();

	bool retx = true;

	qString SSQ = "";

	qValue * program = 0;
	std::vector<qError> allerrors;
	for (std::map<qString, qString>::iterator it = filemap.begin(), end = filemap.end(); it != end; ++it)
	{
		std::vector<qError> errors;
		qValue * ret = 0;
		//currentFile = it->first;
		dab_Parse((char*)it->second.c_str(), &ret, it->first, errors);

		if (ret && ShouldWriteOutput())
		{
			SSQ += "<h1>" + it->first + "</h1>";
			SSQ += "<pre>" + ret->print() + "</pre><hr><ul>" + ret->dumpraw() + "</ul><hr>";
		}

		if (errors.size()) retx = false;
		else
		{
			ret->updateChildren();
			ret->fixPositions(it->first, it->second);

			if (!program) program = ret;
			else
			{
				((qProgram*)program)->AppendProgram((qProgram*)ret);
			}
		}
		std::copy(errors.begin(), errors.end(), std::insert_iterator<std::vector<qError> >(allerrors, allerrors.end()));
	}
	if (retx)
	{
		run_passes(program);

		if (ShouldWriteOutput()) 
			setFile("premov.html", "<ul>" + program->dumpraw() + "</ul>");

		low_MoveDeclarations(program);
		
		low_CheckTypes(program);

		if (ShouldWriteOutput())
		{
			qString RER=
			"<h1>OUTPUT</h1>"
			"<pre>" + program->print() + "</pre><hr><ul>" + program->dumpraw() + "</ul><hr>";
			SSQ += RER;
			setFile("compile_w.html", RER);
		}
	}
	else 
		program = 0;

	if (ShouldWriteOutput())
		setFile("compile.html", SSQ);

	return program;
}
*/