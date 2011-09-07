#include "stdafx.h"
#include "dab_header.h"

std::map<qString, qneu_StructType*> structs;

qneu_Type * TryAddStruct(qString & name)
{
	if (structs.count(name))
	{
		return structs[name];
	}
	return 0;
}

void ResetStruct()
{
	structs.clear();
}

static qValue * caller = 0;

void qValue::updateNewType(const qString & namexxx, qneu_Type * s ) 
{
	if (neu_type)
	{
		qneu_Type * oldtype = neu_type;
		neu_type = neu_type->updateWithType(namexxx, s);
	}
}

void notifyNewType(qString name, qneu_Type * s, qValue * tree ) 
{
	tree->updateNewType(name, s);
	for (int i = 0; i < tree->size(); i++)
	{
		notifyNewType(name, s, (*tree)[i]);
	}
}

void notifyNewType2(qString name, qneu_Type * s, qValue * tree ) 
{
	for (std::map<qString, qneu_StructType*>::iterator it = structs.begin(), end = structs.end(); it != end; it++)
	{
		std::vector<StructMember> & sm = it->second->members;
		std::vector<StructMember> & sm2 = it->second->constver->members;
		for (int k = 0; k < sm.size(); k++)
		{
			qneu_RawType * rr = dynamic_cast<qneu_RawType*>(sm[k].type);
			if (rr && rr->tname == name && rr->is_const == s->is_const)
			{
				sm[k].type = s;
			}
		}
		for (int k = 0; k < sm2.size(); k++)
		{
			qneu_RawType * rr = dynamic_cast<qneu_RawType*>(sm2[k].type);
			if (rr && rr->tname == name && rr->is_const == s->is_const)
			{
				sm2[k].type = s;
			}
		}
	}
}

void add_struct( qStruct * str ) 
{
	qneu_StructType * s = new qneu_StructType();

	for (int i = 0, e = str->L()->size(); i < e; i++)
	{
		qMember * memb = dynamic_cast<qMember*>((*str->L())[i]);	
		StructMember sm;
		sm.type = memb->neu_type;

		sm.name = memb->name;

		s->members.push_back(sm);
	}

	s->stname = str->name;

	if (structs.count(s->stname))
	{
		char msg[9999];
		sprintf(msg, "Struct `%s` already exists.", s->stname.c_str());
		str->fireError(true, ERROR_STRUCT_EXISTS, msg);
		return;
	}

	structs[s->stname] = s;

	s->constver = new qneu_StructType();
	s->constver->constver = s->constver;
	s->constver->is_const = true;
	s->constver->members = s->members;
	s->constver->stname = s->stname;

	notifyNewType(s->stname, s, caller);
	notifyNewType2(s->stname, s, caller);
	notifyNewType(s->stname, s->constver, caller);
	notifyNewType2(s->stname, s->constver, caller);
}

void add_typedef( qTypedef * typedf ) 
{
	notifyNewType(typedf->name, typedf->neu_type, caller);
	notifyNewType2(typedf->name, typedf->neu_type, caller);
}

void get_structs1(qValue * tree)
{
	qStruct * str = dynamic_cast<qStruct*>(tree);
	if (str)
	{
		add_struct(str);
		return;
	}
	qTypedef * typedf = dynamic_cast<qTypedef*>(tree);
	if (typedf)
	{
		add_typedef(typedf);
		return;
	}
	for (int i = 0; i < tree->size(); i++)
	{
		get_structs1((*tree)[i]);
	}
}

void low_GetStructs(qValue * tree)
{
	caller = tree;
	get_structs1(tree);
}
