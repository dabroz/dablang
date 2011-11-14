#include "stdafx.h"
#include "dab_header.h"

void notifyNewFunc(qString name, qneu_Function * f, qValue * tree ) 
{
	qFuncall * fcall = dynamic_cast<qFuncall*>(tree);
	if (fcall)
	{
		if (fcall->name == f->name)
		{
			qString mymangle = "";
			for (int i =0;i<tree->L()->size();i++)
			{
				mymangle+=tree->L()->children[i]->neu_type->mangle();
			}

			if (mymangle == f->mangle)
			{
				fcall->func = f;
			}
		}
	}
	for (int i = 0; i < tree->size(); i++)
	{
		notifyNewFunc(name, f, (*tree)[i]);
	}
}

//std::map<qString, std::vector<qneu_Function *>> functions;

//std::map<qString, Function*> very_raw_funcs;

void ResetFunctions()
{
	//functions.clear();
	//very_raw_funcs.clear();
}

bool qneu_Function::isvararg() const { 
	for (int i =0;i<args.size();i++) if (args[i].type->isVararg())return true;
	return false;
}

void qFuncall::subupdateType()
{
	std::vector<dab_Function> & vv = the_module->_functions[name];
	qSequence * seq = dynamic_cast<qSequence*>(L());
	std::map<qneu_Function*, int> best_score;

	for (int i = 0; i < vv.size(); i++)
	{
		qneu_Function * f = vv[i].node->func;
		int score = 0;
		int maxq = seq->size();
		if(f->isvararg()) 
		{
			maxq=f->args.size()-1;
		}
		else
		{
			if (seq->size() != f->args.size()) continue;
		}

		for (int k = 0; k < maxq; k++)//ns.size(); k++)
		{
			dt_BaseType * atype = (*seq)[k]->neu_type ;
			dt_BaseType * goodtype = f->args[k].type;

			if (atype == 0) 
			{
				score=9999;
				return ;
				break;
			}
			if (atype == goodtype) { }
			else if (atype->can_cast_to(goodtype)) { score++; }
			else {
				score = 9999;
			}
		}
		best_score[f] = score;
	}

	int qbest_score = 500;
	qneu_Function * fbest = 0;

	for (std::map<qneu_Function*, int>::iterator it = best_score.begin(), end = best_score.end(); it != end; ++it)
	{
		if (it->second < qbest_score) { qbest_score = it->second; fbest = it->first; }
	}

	if (!fbest)
	{
		char msg[9999];

		if (vv.size()==0)
		{
			sprintf(msg, "Function `%s` doesn't exist.", name.c_str());
			fireError(true, ERROR_FUNCTION_DOESNT_EXIST, msg);
		}
		else
		{
			qString papa;
			for (int i =0;i<seq->size(); i++)
			{	
				if (i) papa+=", ";
				papa += seq->children[i]->neu_type->name();
			}
			sprintf(msg, "No matching call for `%s(%s)`.", name.c_str(), papa.c_str());
			fireError(true, ERROR_NO_MATCHING_CALL, msg);

			for (int i = 0; i< vv.size(); i++)
			{
				qString papa;
				for (int j =0;j<vv[i].node->func->args.size(); j++)
				{	
					if (j) papa+=", ";
					papa += vv[i].node->func->args[j].type->name();
				}
				//           "No matching call for `
				sprintf(msg, "Candidates are:      `%s(%s)`", name.c_str(), papa.c_str());
				fireError(true, ERROR_NO_MATCHING_CALL, msg);
			}
		}

		return;
	}

	int maxk2=seq->size();
	if  (fbest->isvararg()) maxk2 = fbest->args.size()-1;
	for (int k = 0; k < seq->size(); k++)//ns.size(); k++)
	{
		if (k< maxk2)
		{
			if ((*seq)[k]->neu_type != fbest->args[k].type) 
		 {
			 char msg[9999];
			 sprintf(msg,"Argument %d of `%s`: ", k+1, name.c_str());
			 qValue * nv = new qConvert(fbest->args[k].type, (*seq)[k], msg);
			 seq->replace_child((*seq)[k], nv);
		 }
		}
	}

	this->neu_type = fbest->returntype;
	this->func = fbest;
}

qneu_Function::qneu_Function( class qFunction * fun )
{
	this->name = fun->name;
	this->returntype = fun->neu_type;
	this->mangled_name = "_f_"+ fun->name+"_";
	this->mangle = "";
	for (int i = 0; i < fun->L()->size(); i++)
	{
		qDeclare * arg = dynamic_cast<qDeclare*>(fun->L()->children[i]);

		FunctionArg a;
		a.name = arg->name;
		a.type = arg->neu_type;

		this->args.push_back(a);

		this->mangle += a.type->mangle();
	}
	this->mangled_name += this->mangle;

	void AddDablangStatus(const qString & ss);
	AddDablangStatus("* loaded function `" +  this->mangled_name + "`");
	fun->func = this;

	llvmd = 0;
}
/*
void create_func(qValue * prog,qFunction * f)
{
	qneu_Function * func = new qneu_Function(f);
	functions[func->name].push_back(func);
}

void low_FindFunctions(qValue * pro)
{
	for (int i = 0;i<pro->size();i++)
	{
		qValue * tree = pro->children[i];
		qFunction * f= dynamic_cast<qFunction *>(tree);
		if (f) create_func(pro,f);
	}
}*/