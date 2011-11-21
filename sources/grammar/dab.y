%{
#include "stdafx.h"
#include "dab_header.h"

#define QCODEX(xxx) QCODE(q_yy_pos(scanner), (xxx))

int bisonfprintf(FILE * file, const char * format, ...);
#define YYERROR_VERBOSE 1
#define YYFPRINTF bisonfprintf

int isatty(int foo) { return -1; }

size_t q_yy_pos(void*scanner);

void dab_Parse(char *buf, qValue **result, const std::string & filename, std::vector<qError> & errors, dab_Module * module)
{
    parse_parm  pp;

    pp.buf = buf;
    pp.length = strlen(buf);
    pp.pos = 0;
    pp.filename = filename;
    pp.errorsfound = 0;
    pp.module = module;
    
    *result = 0;
    yylex_init(&pp.yyscanner);
    yyset_extra(&pp, pp.yyscanner);
    yyparse(&pp, pp.yyscanner);
    *result = pp.result;
    yylex_destroy(pp.yyscanner);
    
    errors = pp.errors;
}

%}

%pure_parser
%parse-param {parse_parm *parm}
%parse-param {void *scanner}
%lex-param {yyscan_t *scanner}

%token INT FLOAT BOOL NAME RETURN IF ELSE WHILE FOR STRUCT EXTERN STRING VARARG BREAK TYPEDEF CONST CAST

%left PLUSPLUS MINUSMINUS
%left PLUSEQ MINUSEQ MULEQ DIVEQ
%left BAND 
%left BOR
%left EQ NEQ
%left '<' '>'
%left '&'
%left '|'
%left '-' '+'
%left '*' '/'
%left '!'
%right NEG POS EQNEG ADDROF DEREF
%left '[' ']'
%left PACC
%left '.'

%left CONST
%left CAST

%%

result 
	: program 							{ parm->result = $1; }
	|									{ parm->result = qtree_program_start(0); }
	;
	
program
	: program definition 				{ $$ = qtree_program_append($1, $2); }
	| program error 					{ $$ = $1; yyclearin; yyerrok; }
	| definition 						{ $$ = qtree_program_start($1); }
	| error 							{ yyclearin; yyerrok; }
	;
	
definition
	: type NAME ';' 												{ $$ = QCODEY($2, qtree_globalvar($1, $2, 0)); }
	| type NAME '=' constant ';' 									{ $$ = QCODEY($2, qtree_globalvar($1, $2, $4)); }	
	| EXTERN optionaalearglist type NAME '(' arglistnull ')' ';'	{ $$ = QCODEY($4, new qExternFunc($2, $3, $4, $6)); }
	| '[' NAME ']' type NAME '(' arglistnull ')' ';'				{ $$ = QCODEY($4, new qExternFunc($2, $4, $5, $7, 1)); }
	| type NAME '(' arglistnull ')' block 							{ $$ = QCODEY($2, qtree_function($1, $2, $4, $6)); }
	| STRUCT NAME '{' strmember '}' ';'								{ $$ = QCODEY($2, qtree_struct($2, $4)); }
	| TYPEDEF type NAME ';'											{ $$ = QCODEY($3, new qTypedef($3, $2)); }
	;

optionaalearglist
	: '(' earglist ')'  { $$ = $2; }
	|					{ $$ = 0; }
	;

earglist
	: earglist ',' STRING	{ $$ = qtree_seq_append($1, $3); }
	| STRING				{ $$ = qtree_seq_start($1); }
	;

strmember
	: strmember type NAME ';'			{ $$ = qtree_seq_append($1, QCODEY($3, qtree_smember($2, $3))); }
	| type NAME ';'						{ $$ = qtree_seq_start(qtree_smember($1, $2)); }
	;

arglistnull : arglist | { $$ = 0; } ;

arglist
	: arglist ',' type NAME 			{ $$ = qtree_seq_append($1, qtree_declare($3, $4)); } 
	| arglist ',' VARARG				{ $$ = qtree_seq_append($1, qtree_vararg()); }
	| type NAME 						{ $$ = qtree_seq_start(qtree_declare($1, $2)); }
	; 

funcall
	: NAME '(' paramlist ')'					{ $$ = QCODEY($1, qtree_funcall($1, $3)); }
	| NAME '(' ')' 								{ $$ = QCODEY($1, qtree_funcall($1, 0)); }
	;
	
instr
	: expr ';'
	| block
	| IF '(' math ')' instr 					{ $$ = qtree_if($3, $5, 0); }
	| IF '(' math ')' instr ELSE instr			{ $$ = qtree_if($3, $5, $7); }
	| WHILE '(' math ')' instr					{ $$ = qtree_while($3, $5); }
	| FOR '(' expr ';' math ';' expr ')' instr	{ $$ = qtree_for($3, $5, $7, $9); }
	| funcall ';'
	| RETURN math ';'							{ $$ = qtree_return($2); }
	| BREAK ';'										{ $$ = QCODEX(new qBreak()); }
	;
	
block
	: '{' seq '}' 						{ $$ = qtree_block($2); }
	| '{' '}'							{ $$ = 0; }
	;

seq
	: seq instr 						{ $$ = qtree_seq_append($1, $2); }	
	| seq error 						{ $$ = $1; yyclearin; yyerrok; }	
	| instr 							{ $$ = qtree_seq_start($1); }	
	| error 							{ yyclearin; yyerrok; }
	;
	
expr
	: type NAME 						{ $$ = QCODEY($1, qtree_declare($1, $2)); }
	| type NAME '=' math 				{ $$ = QCODEY($1, qtree_declare_value($1, $2, $4)); }
	| var '=' math 						{ $$ = QCODEY($1, qtree_assign($1, $3)); }
	| var PLUSEQ math 					{ $$ = QCODEY($1, qtree_assign($1, qtree_binop("add", $1, $3))); }
	| var MINUSEQ math 					{ $$ = QCODEY($1, qtree_assign($1, qtree_binop("sub", $1, $3))); }
	| var MULEQ math 					{ $$ = QCODEY($1, qtree_assign($1, qtree_binop("mul", $1, $3))); }
	| var DIVEQ math 					{ $$ = QCODEY($1, qtree_assign($1, qtree_binop("div", $1, $3))); }
	| var PLUSPLUS						{ $$ = QCODEY($1, qtree_assign($1, qtree_binop("add", $1, qtree_constant_int(1)))); }
	| var MINUSMINUS					{ $$ = QCODEY($1, qtree_assign($1, qtree_binop("sub", $1, qtree_constant_int(1)))); }
	;

math
    : math EQ math 						{ $$ = QCODEY($1, qtree_binop("eq",   $1, $3)); }
    | math NEQ math 					{ $$ = QCODEY($1, qtree_binop("neq",  $1, $3)); }
    | math '>' math 					{ $$ = QCODEY($1, qtree_binop("gt",   $1, $3)); }
    | math '<' math 					{ $$ = QCODEY($1, qtree_binop("lt",   $1, $3)); }
    | math BAND math 					{ $$ = QCODEY($1, qtree_binop("band", $1, $3)); }
    | math BOR math 					{ $$ = QCODEY($1, qtree_binop("bor",  $1, $3)); }
    | math '&' math 					{ $$ = QCODEY($1, qtree_binop("and",  $1, $3)); }
    | math '|' math 					{ $$ = QCODEY($1, qtree_binop("or",   $1, $3)); }
	| math '+' math 					{ $$ = QCODEY($1, qtree_binop("add",  $1, $3)); }
    | math '-' math 					{ $$ = QCODEY($1, qtree_binop("sub",  $1, $3)); }
    | math '*' math 					{ $$ = QCODEY($1, qtree_binop("mul",  $1, $3)); }
    | math '/' math 					{ $$ = QCODEY($1, qtree_binop("div",  $1, $3)); }
    | '-' math %prec NEG 				{ $$ = QCODEY($2, qtree_unop("neg",   $2)); }
    | '!' math %prec EQNEG 				{ $$ = QCODEY($2, qtree_unop("not", $2)); }
    | '(' math ')' 						{ $$ = $2; }
	| constant
	| var
	| funcall
	| CAST '<' type '>' math	%prec CAST		{ $$ = QCODEY($5, new qConvert($3->neu_type, $5, "!!")); }
    ;

constant
    : INT
	| FLOAT
	| STRING
	| BOOL
	;

paramlist
	: paramlist ',' math				{ $$ = qtree_seq_append($1, $3); }
	| math								{ $$ = qtree_seq_start($1); }
	;

type
	: NAME 								{ $$ = QCODEY($1, qtree_type(parm->module, $1)); }
	| type '*'							{ $$ = QCODEY($1, new qTypeHolder($1->neu_type->createPointer())); }
	| CONST type						{ $$ = QCODEY($2, new qTypeHolder($2->neu_type->CreateConst())); }
	| type '<' INT '>'					{ $$ = QCODEY($1, new qTypeHolder($1->neu_type->CreateArray($3))); }
	;
	
var
	: var '.' NAME						{ $$ = QCODEY($1, qtree_subvariable($1, $3)); }
	| var PACC NAME						{ $$ = QCODEY($1, qtree_subvariable(new qDereference($1), $3)); }
	| NAME								{ $$ = QCODEY($1, qtree_variable($1)); }
    | '&' var %prec ADDROF 				{ $$ = QCODEY($2, new qPointer($2)); }
    | '*' var %prec DEREF				{ $$ = QCODEY($2, new qDereference($2)); }
    | '(' var ')'						{ $$ = $2; }
    | var '[' math ']'					{ $$ = QCODEY($1, new qArrayAccess($1, $3)); }
	;
	
%%
