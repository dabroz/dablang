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
	qdtprintf("'%s' notifies struct '%s%s'\n", newTypeName.c_str(), ((st->isConst())?"const ":""), st->name().c_str());
	for (int i = 0; i < st->members.size(); i++)
	{
		StructMember & sm = st->members[i];
		
		if (sm.type->isRaw() && sm.type->rawname() == newTypeName && sm.type->isConst() == newType->isConst())
		{
			//qdtprintf("'%s' -> '%s%s' :: replaced field '%s'\n",  newTypeName.c_str(), ((st->isConst())?"const ":""), st->name().c_str(),
			//	sm.name.c_str());
			sm.type = newType;
		}
	}
}

void di_NotifyAboutType(const std::string & name, dt_BaseType * type, dab_Module * module)
{
	//qdtprintf("di_NotifyAboutType('%s')\n", name.c_str());
	for (dab_Module::it_f it = module->_functions.begin(), end = module->_functions.end(); it != end; ++it)
	{
		for (unsigned i = 0; i < it->second.size(); i++)
		{
			qFunction * f = it->second[i].node;
			notifyNewType(name, type, f);
		}
	}
	for (dab_Module::it_t it = module->_typedefs.begin(), end = module->_typedefs.end(); it != end; ++it)
	{
		notifyNewType(name, type, it->second.node);
	}
	for (dab_Module::it_s it = module->_structs.begin(), end = module->_structs.end(); it != end; ++it)
	{
		notifyNewType(name, type, it->second.node);
		if (it->second.type)
		{
			notifyStruct(name, type, it->second.type, module);
			notifyStruct(name, type, it->second.type->constver, module);
		}
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
