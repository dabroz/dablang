%{
#include "stdafx.h"
#include "dab_header.h"
#include "dab_symbols.h"

#define PARM    yyget_extra(yyscanner)
#define YY_NO_UNISTD_H 1

int isatty(int);
void comment();
void commentline();

size_t q_yy_pos(void*scanner);

int atoix(const char * ss);

#define QCODELEX(xxx) QCODE(q_yy_pos(yyscanner), (xxx))

size_t lexlexfwrite(const void *buffer, size_t size, size_t count, FILE *stream);

#define ECHO lexlexfwrite( yytext, yyleng, 1, yyout )

#define YY_INPUT(buffer, res, max_size)             \
do {                                                \
if (PARM->pos >= PARM->length)                  \
    res = YY_NULL;                              \
else                                            \
{                                               \
    res = PARM->length - PARM->pos;             \
    res > 1/*(int)max_size*/ ? res = /*max_size*/1 : 0;   \
    memcpy(buffer, PARM->buf + PARM->pos, res); \
    PARM->pos += res;                           \
}                                               \
} while (0)

%}

%option reentrant bison-bridge
%option noyywrap
%option nounput

%x IN_COMMENT
%x IN_LINECOMMENT

%%

<INITIAL>
{
     "/*"              BEGIN(IN_COMMENT);
     "//"				BEGIN(IN_LINECOMMENT);

"return" { return (RETURN); }
"if" { return (IF); }
"else" { return (ELSE); }
"while" { return (WHILE); }
"for" { return (FOR); }
"struct" { return (STRUCT); }
"extern" { return (EXTERN); }
"..." { return (VARARG); }
"break" { return (BREAK); }
"typedef" { return (TYPEDEF); }
"const" { return (CONST); }
"cast" { return (CAST); }

"true" {  *yylval = QCODELEX(new qConstant(TYPE_BOOL, true)); return (BOOL); }
"false" {  *yylval = QCODELEX(new qConstant(TYPE_BOOL, false)); return (BOOL); }

0x([\-]*[0-9A-Fa-f]+) { *yylval = QCODELEX(qtree_constant_int(atoix(yytext))); return (INT); }
([\-]*[0-9]+) { *yylval = QCODELEX(qtree_constant_int(atoi(yytext))); return (INT); }

([\-]*[0-9]*\.[0-9]+)f { *yylval = QCODELEX(qtree_constant_float((float)atof(yytext))); return (FLOAT); }
([\-]*[0-9]*\.[0-9]+) { *yylval = QCODELEX(qtree_constant_float((float)atof(yytext))); return (FLOAT); }

\"(\\.|[^\\"])*\" { *yylval = QCODELEX(new qStringConstant(yytext)); return (STRING); }

([a-zA-Z_]([a-zA-Z0-9_]*)) { *yylval = QCODELEX(qtree_id(yytext)); return (NAME); }

"+=" { return (PLUSEQ); }
"-=" { return (MINUSEQ); }
"*=" { return (MULEQ); }
"/=" { return (DIVEQ); }
"++" { return (PLUSPLUS); }
"--" { return (MINUSMINUS); }
"||" { return (BOR); }
"&&" { return (BAND); }
"==" { return (EQ); }
"!=" { return (NEQ); }
"->" { return (PACC); }

"." { return (*yytext); }

"[" { return (*yytext); }
"]" { return (*yytext); }

[!+\-*/&|(),=;{}<>] { return (*yytext); }

[ \t\r\n]+ 

}
<IN_COMMENT>
{
     "*/"      BEGIN(INITIAL);
     [^*\n]+   // eat comment in chunks
     "*"       // eat the lone star
     \n        yylineno++;
}
<IN_LINECOMMENT>
{
    [^\n]+   // eat comment in chunks
	\n		BEGIN(INITIAL);
}

%%

const char * q_yy_buf(void*scanner)
{
	yyscan_t yyscanner = (yyscan_t)scanner;
	return PARM->buf;
}
size_t q_yy_pos(void*scanner)
{
	yyscan_t yyscanner = (yyscan_t)scanner;
	return PARM->pos;
}
