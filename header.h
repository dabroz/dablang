#pragma once

#include <vector>
#include <string>
#include <assert.h>

using namespace std;

enum
{
	TYPE_UNKNOWN,
	TYPE_VOID,
	TYPE_FLOAT,
	TYPE_FLOAT4,
	TYPE_BOOL,

	TYPE_INT8,
	TYPE_INT16,
	TYPE_INT32,
	TYPE_INT64,

	TYPE_UINT8,
	TYPE_UINT16,
	TYPE_UINT32,
	TYPE_UINT64,

	TYPE_DOUBLE,

};

struct float4
{
	union
	{
		float x, y, z, w;
		float m[4];
	};
};

struct parse_parm
{
	void		*yyscanner;
	char		*buf;
	int			pos;
	int			length;
	class qValue	*result;
};

void parse(char *buf, qValue **result);

#define YYSTYPE         qValue*
#define YY_EXTRA_TYPE   parse_parm *

int     yylex(YYSTYPE *, void *);
int     yylex_init(void **);
int     yylex_destroy(void *);
void    yyset_extra(YY_EXTRA_TYPE, void *);
int     yyparse(parse_parm *, void *);
void    yyerror(parse_parm *parm,void*scanner,const char*msg);

#define YYDEBUG 1

#include "qdt3.h"

struct qError
{
	int num;
	int error; // 1 error 0 warning
	qString desc;
	qString file;
	int line;
	int start;
	//int end;

	qError() { num = 0; error = 1; desc = "?"; file = "?"; line = 1; start = 1; }

	bool operator < (const qError & other)
	{
		if (file != other.file) return file < other.file;
		if (line != other.line) return line < other.line;
		return start < other.start;
	}
};

extern std::vector<qError> compileErrors;

qValue * QCODE(int pos, qValue *r);
inline qValue * QCODEY(qValue * from, qValue * to)
{
	to->loc = from->loc;
	return to;
}

enum 
{
	ERROR_SYNTAX_ERROR					= 1,
	ERROR_FUNCTION_DOESNT_EXIST			= 2,
	ERROR_NO_MATCHING_CALL				= 3,
	ERROR_STRUCT_EXISTS					= 4,
	ERROR_SUBVAR_ERROR					= 5,
	ERROR_SUBVAR_DOESNTEXIST			= 6,
	WARNI_IMPLICIT_CONVERT				= 7,
	ERROR_VAR_NOT_FOUND					= 8,
	ERROR_TYPE_ERROR					= 9,
	ERROR_NO_BINOP						= 10,
	ERROR_TYPE_NO_POINTER				= 11,
	ERROR_TYPE_RAWTYPE					= 12,

	MAX_ERROR_NUM
};
