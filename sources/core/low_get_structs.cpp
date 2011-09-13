#include "stdafx.h"
#include "dab_header.h"

void qValue::updateNewType(const qString & namexxx, dt_BaseType * s ) 
{
	if (neu_type)
	{
		dt_BaseType * oldtype = neu_type;
		neu_type = neu_type->updateWithType(namexxx, s);
	}
}

void notifyNewType(const qString & name, dt_BaseType * s, qValue * tree ) 
{
	tree->updateNewType(name, s);
	for (int i = 0; i < tree->size(); i++)
	{
		notifyNewType(name, s, (*tree)[i]);
	}
}

void notifyStruct(const qString & newTypeName, dt_BaseType * newType, qneu_StructType * st, dab_Module * module) 
{
	for (int i = 0; i < st->members.size(); i++)
	{
		StructMember & sm = st->members[i];
		
		if (sm.type->isRaw() && sm.name == newTypeName && sm.type->isConst() == newType->isConst())
		{
			sm.type = newType;
		}
	}
}

void di_NotifyAboutType(const std::string & name, dt_BaseType * type, dab_Module * module)
{
	for (std::map<std::string, dab_Function>::iterator it = module->_functions.begin(), end = module->_functions.end(); it != end; ++it)
	{
		qFunction * f = it->second.node;
		notifyNewType(name, type, f);
	}
	for (std::map<std::string, dab_Struct>::iterator it = module->_structs.begin(), end = module->_structs.end(); it != end; ++it)
	{
		notifyStruct(name, type, it->second.type, module);
		notifyStruct(name, type, it->second.type->constver, module);
	}
}

qneu_StructType * di_CreateStruct(qStruct * str, dab_Module * module)
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

	/*if (structs.count(s->stname))
	{
		char msg[9999];
		sprintf(msg, "Struct `%s` already exists.", s->stname.c_str());
		str->fireError(true, ERROR_STRUCT_EXISTS, msg);
		return;
	}*/

	s->constver = new qneu_StructType();
	s->constver->constver = s->constver;
	s->constver->is_const = true;
	s->constver->members = s->members;
	s->constver->stname = s->stname;

	return s;
}

/*
void notifyNewType2(qString name, dt_BaseType * s, qValue * tree ) 
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
*/
