#include "stdafx.h"
#include "dab_header.h"

qString qValue::dumprawX()
{
	return qString(typeid(*this).name()).substr(7) + " " + name + " " + printType(neu_type)+" "+subdump();
}

qString qValue::dumpraw()
{
	qString tt = "<i>" + printType(neu_type)+"</i> ";
	if (IsNoValue()) tt="";

	qString ss1 = qString(typeid(*this).name()).substr(7) + " <b>" + name + "</b> "+tt+"<u>"+subdump()+"</u>";

	char kka[128];
	sprintf(kka,"%d",loc.cmp_line);
	ss1 += " <span style='color:gray'>" + loc.cmp_file + ":" + kka + "</span>";

	qString ret = "<li>" +  ss1+ "</li>\n";
	if (size())
	{
		ret += "<ul>\n";
		for (int i = 0; i < size(); i++) ret += children[i]->dumpraw();
		ret += "</ul>\n";
	}
	return ret;
}

qString qValue::dump()
{
	qString TTT = typeid(*this).name();
	TTT = TTT.substr(7);

	qString ret = "<div class=\"";

	ret += TTT;
	if (name.length())
	{
	ret +=  " n" + name;
	}
	ret +="\"><span>";

	TTT="";

	if (!isInstruction())
		ret += "<em>" + printType(neu_type) + "</em>";

	if (name.length())
	{
		ret += "<b>"+name+"</b>";
	}

	ret += "<u>";
	ret += subdump();
	ret += "</u>";

	ret += "</span>\n";
	if (size())
	{
		ret += "<ul>";
		for (size_t i = 0, e = size(); i < e; i++)
		{
			ret += children[i]->dump();
		}
		ret += "</ul>";
	}
	ret += "</div>\n";
	return ret;
}

void debugqv(const char * name, ...)
{
	qValue * v = 0;
	va_list list;
	va_start(list, name);
	printf("%-20s -->", name);
	while (v = va_arg( list, qValue*))
	{
		printf(" [%s]", v->print().c_str());
	}
	printf("\n");
	va_end(list);
}

qString mangleType(dt_BaseType * type)
{
	return type->mangle();
}

qString mangle(const char * name, qValue * arglist)
{
	qString ret = "_" + qString(name) + "_";

	for (size_t i = 0, e = arglist->size(); i < e; i++)
	{
		ret += mangleType((*arglist)[i]->neu_type);
	}

	return ret;
}

bool qFunctionExists(const char * name)
{
	return false;
}

int qFunctionType(const char * name)
{
	return 0;
}

qString binSym(const qString &name)
{
	if (name == "add") return "+";
	if (name == "sub") return "-";
	if (name == "mul") return "*";
	if (name == "div") return "/";
	if (name == "lt") return "<";
	if (name == "gt") return ">";

	return "????";
}

void qValue::gatherVariables()
{
	for (int i = 0; i < size(); i++)
	{
		qValue * c = children[i];

		c->variablesavail = this->variablesavail;
		c->gatherVariables();
	}
}

class qFunction * qValue::function()
{
	qFunction  * f = dynamic_cast<qFunction *>(this);
	if (f) return f;
	if (!parent) return 0;
	return parent->function();
}

void qValue::backtrace(int q)
{
	qdtprintf("this %p parent %p %2d: %s\n", this, parent, q, dumprawX().c_str());
	if (parent) parent->backtrace(q+1);
}

void qValue::fireError( bool error, int num, const qString & desc )
{
	qError err;
	err.error = error?1:0;
	err.num = num;
	err.file = loc.cmp_file;
	err.line = loc.cmp_line;
	err.start = loc.cmp_col;
	err.desc = desc;

	qdtprintf("ERROR <%s> (%s:%d)\n", desc.c_str(), loc.cmp_file.c_str(), loc.cmp_line);
	//TODO! compileErrors.push_back(err);
}


std::string dab_Module::Dump() 
{
	std::string ret;

	ret += "<h2>Globals</h2><ul>";
	for (it_g it = _globals.begin(), end = _globals.end(); it != end; ++it)
	{
		ret += "<li>" + it->second->dumprawX() + "</li>";
	}
	ret += "</ul><hr>";
	ret += "<h2>Structs</h2>";
	for (it_s it = _structs.begin(), end = _structs.end(); it != end; ++it)
	{
		dab_Struct & s = it->second;

		if (!s.type) { ret += "<h3>ERROR '" + s.node->name + "'</h3>"; continue; }
		
		ret += "<h3>" + s.type->name() + "</h3>";

		ret += "<table border><tr><th>Name</th><th colspan=2>Type</th></tr>";
		for (int j = 0; j < s.type->members.size(); j++)
		{
			StructMember & sm = s.type->members[j];
			ret += "<tr><td>" + sm.name + "</td><td>"+qString(typeid(*sm.type).name()).substr(6)+"</td><td>" + sm.type->name() + "</td></tr>";
		}
		ret += "</table>";
	}
	ret += "<hr>";
	ret += "<h2>Typedefs</h2><ul>";
	for (it_t it = _typedefs.begin(), end = _typedefs.end(); it != end; ++it)
	{
		dab_Typedef & t = it->second;

		ret += t.node->dumpraw();
	}
	ret += "</ul><hr>";
	ret += "<h2>Functions</h2>";
	for (it_f it = _functions.begin(), end = _functions.end(); it != end; ++it)
	{
		for (unsigned i = 0; i < it->second.size(); i++)
		{
			dab_Function & f = it->second[i];

			ret += "<h3>" + f.node->name + "</h3>";
			ret += "<ul>" + f.node->dumpraw() + "</ul>";
		}
	}

	return ret;
}


bool qValue::remove_from_parent()
{
	for (int i =0; i < parent->size(); i++)
	{
		if (parent->children[i]==this)
		{
			parent->children.erase(parent->children.begin() + i);
			parent->updateChildren();
			parent = 0;
			return true;
		}
	}
	return false;
}

bool qValue::replace_child(qValue * from, qValue * to)
{
	for (int i =0; i < size(); i++)
	{
		if (children[i]==from)
		{
			from->parent = 0;
			children[i] = to;
			updateChildren();
			return true;
		}
	}
	return false;
}

bool qValue::replace_in_parent(qValue * newvalue)
{
	for (int i =0; i < parent->size(); i++)
	{
		if (parent->children[i]==this)
		{
			parent->children[i] = newvalue;
			newvalue->parent = parent;
			parent->updateChildren();
			parent = 0;
			return true;
		}
	}
	return false;
}

bool qValue::is_parent(qValue * v)
{
	if (this==v) return true;
	if (!parent) return false;
	return parent->is_parent(v);
}

qValue::qValue() : neu_type(0), parent((qValue*)0)
{
	loc.cmp_pos=-1;
};

void qValue::updateChildren()
{
	for (size_t i = 0, e = size(); i < e; i++)
	{
		children[i]->parent = this;
		children[i]->updateChildren();
	}
}

void qValue::fixPositions( const qString & file, const qString & str , class dab_Module * m) 
{
	the_module = m;

	void getlinefrompos(const qString & text, int pos, int & line, int & col);

	loc.cmp_file = file;
	getlinefrompos(str, loc.cmp_pos, loc.cmp_line, loc.cmp_col);

	for (int i = 0; i < size(); i++)
	{
		children[i]->fixPositions(file, str, m);
	}
}