#include "qdt3.h"

qTypedef::qTypedef( qValue * xxname, qValue * xxtype )
{
	name = xxname->name;
	neu_type = xxtype->neu_type;
}

qString qTypedef::print( int indent /*= 0*/ )
{
	return "TYPEDEF `" + name + "` is alias for `" + neu_type->name() + "`";
}
