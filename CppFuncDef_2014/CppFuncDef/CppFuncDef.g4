grammar CppFuncDef;

@parser::members
{
	protected const int EOF = Eof;
}
 
@lexer::members
{
	protected const int EOF = Eof;
	protected const int HIDDEN = Hidden;
}

/*
 * Parser Rules
 */

cppFunction
	:	
		DATATYPE STAR* CALLINGCONV? ID
		LEFTPAREN (DATATYPE STAR* ID (COMMA DATATYPE STAR* ID)*)? RIGHTPAREN
		LEFTBRACKET
			(declarORassign SEMICOLON | expression SEMICOLON | RETURNTOKEN expression SEMICOLON | whileStruct | forStruct)*
			RETURNTOKEN expression SEMICOLON	
			(declarORassign SEMICOLON | expression SEMICOLON | RETURNTOKEN expression SEMICOLON | whileStruct | forStruct)*
		RIGHTBRACKET

		|
		
		VOIDTOKEN CALLINGCONV? ID
		LEFTPAREN (DATATYPE STAR* ID (COMMA DATATYPE STAR* ID)*)? RIGHTPAREN
		LEFTBRACKET 
			(declarORassign SEMICOLON | expression SEMICOLON | RETURNTOKEN SEMICOLON | whileStruct | forStruct)*
		RIGHTBRACKET
	;

declarORassign
	:	( DATATYPE? ID (ASSIGNTOKEN expression)? | ID (ADDASSIGN | SUBASSIGN | MULASSIGN | DIVASSIGN) expression )
	;

expression
	:	expression (EQUALTOKEN | LESSEQUAL | MOREEQUAL | NEGEQUAL | MORETOKEN | LESSTOKEN) expression
		| expression (PLUSTOKEN | SUBTOKEN | STAR | DIVTOKEN) expression
		| expression (ANDTOKEN | ORTOKEN | ANDSINGLE | ORSINGLE) expression
		| LEFTPAREN expression RIGHTPAREN
		| ID
		| FIG
		| CH
		| STR
		| NEGTOKEN expression
	;

whileStruct
	:	WHILETOKEN LEFTPAREN expression RIGHTPAREN
		LEFTBRACKET
			(declarORassign SEMICOLON | expression SEMICOLON | BREAKTOKEN SEMICOLON | CONTINUETOKEN SEMICOLON | whileStruct | forStruct)*
		RIGHTBRACKET
	;

forStruct
	:	FORTOKEN LEFTPAREN ((declarORassign | expression) (COMMA (declarORassign | expression))*)? SEMICOLON (expression (COMMA expression)*)? SEMICOLON  ((declarORassign | expression) (COMMA (declarORassign | expression))*)? RIGHTPAREN
		LEFTBRACKET
			(declarORassign SEMICOLON | expression SEMICOLON | BREAKTOKEN SEMICOLON | CONTIINUETOKEN SEMICOLON | whileStruct | forStruct)*
		RIGHTBRACKET
	;

/*
 * Lexer Rules
 */

WS
	:	(' ' | '\t' | '\n' | '\r')+ -> skip
	;

ANDTOKEN
	:	'&&'
	;

ORTOKEN
	:	'||'
	;

EQUALTOKEN
	:	'=='
	;

LESSEQUAL
	:	'<='
	;

MOREEQUAL
	:	'>='
	;

NEGEQUAL
	:	'!='
	;

ADDASSIGN
	:	'+='
	;

SUBASSIGN
	:	'-='
	;

MULASSIGN
	:	'*='
	;

DIVASSIGN
	:	'/='
	;

NEGTOKEN
	:	'!'
	;

PLUSTOKEN
	:	'+'
	;

SUBTOKEN
	:	'-'
	;

DIVTOKEN
	:	'/'
	;

ASSIGNTOKEN
	:	'='
	;

LESSTOKEN
	:	'<'
	;

MORETOKEN
	:	'>'
	;

STAR
	:	'*'
	;

SEMICOLON
	:	';'
	;

COMMA
	:	','
	;

ANDSINGLE
	:	'&'
	;

ORSINGLE
	:	'|'
	;

LEFTBRACKET
	:	'{'
	;

RIGHTBRACKET
	:	'}'
	;

LEFTPAREN
	:	'('
	;

RIGHTPAREN
	:	')'
	;

// ----------------------------------------------------

CH
	:	'\'' . '\''
	;

STR
	:	'\"' .* '\"'
	;

// -----------------------------------------------------


WHILETOKEN
	:	'while'
	;

FORTOKEN
	:	'for'
	;

RETURNTOKEN
	:	'return'
	;

VOIDTOKEN
	:	'void'
	;

BREAKTOKEN
	:	'break'
	;

CONTINUETOKEN
	:	'continue'
	;



DATATYPE
	:	'int' | 'short' | 'long' | 'float' | 'double' | 'char' | 'bool' | 'wchar_t'
	;

ID
	:	([a-zA-Z] | '_') ([a-zA-Z] | '_' | [0-9])*
	;

CALLINGCONV
	:	'_' ('stdcall' | 'cdecl' | 'fastcall')
	;

// -----------------------------------------------------

FIG
	:	[0-9]+ ('.' [0-9]+)?
	;