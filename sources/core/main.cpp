#include "stdafx.h"
#include "dab_header.h"
#include "dab_internal.h"

bool produce_output = false;

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

void setFile(const char *name, const qString&body)
{
	FILE * f = fopen(name, "wb");
	fwrite(body.c_str(), 1, body.length() + 1, f);
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

void run_passes(qValue * v, bool nostructures=false)
{
	//if (!nostructures) low_GetStructs(v);
	low_FindFunctions(v);

	low_ReplaceForWhile(v);
	v->gatherVariables();
	low_UpdateVarReferences(v);
	v->updateType();
	low_FixReturnConverts(v);
}

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

bool subupdatecompiled(const char *txt, qValue * last)
{
	UPDATING_JIT_CODE  = true;
	originalCode =last;
	//ERRORS_FOUND = 0;

	qValue * ret = 0;
	//currentFile = "__virtual_update.dab";
	std::vector<qError> errors;
	dab_Parse((char*)txt, &ret, "__virtual_update.dab", errors, 0);

	if (errors.size()) return false;

	ret->updateChildren();
	ret->fixPositions("__virtual_update.dab", txt);

	for (int i = 0 ;i<ret->size();i++)
	{
		if (dynamic_cast<qDeclare*>(ret->children[i]))
		{
			ret->children[i]->remove_from_parent();
			i--;
		}
	}

	qProgram * prog0 = (qProgram*)originalCode;
	qProgram * prog1 = (qProgram*)ret;

	for (std::map<qString, qDeclare*>::iterator it = prog0->globalvars.begin(), end = prog0->globalvars.end(); it != end; ++it)
	{
		prog1->globalvars[it->first] = it->second;
	}

	run_passes(ret,true);
	low_MoveDeclarations(ret);
	low_CheckTypes(ret);

	updateCode = ret;

	if (ShouldWriteOutput()) 
		setFile("UPDATE.html", "<ul>" + ret->dumpraw() + "</ul>");

	return true;
}


DABCORE_API dab_Module * dab_CompileFiles(std::map<qString, qString> & files, dab_Module * module)
{
	setlocale(LC_ALL,"C");
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
			ret->fixPositions(it->first, it->second);
			module->Append(ret);
		}
	}

	module->ProcessTypes();
	
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
			_functions[f->name] = f;
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