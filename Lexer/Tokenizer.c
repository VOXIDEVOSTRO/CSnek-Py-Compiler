#include <PyTokens.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <Main.h>

/**
 * Match The Token
 */
PyTokenCat
MirrorCheckToken(const char *text)
{
    if (strcmp(text, "def") 		== 0) return 	DEF;
    if (strcmp(text, "return") 		== 0) return 	RETURN;
    if (strcmp(text, "if") 			== 0) return 	IF;
    if (strcmp(text, "else") 		== 0) return 	ELSE;
    if (strcmp(text, "elif") 		== 0) return 	ELIF;
    if (strcmp(text, "while") 		== 0) return 	WHILE;
    if (strcmp(text, "for") 		== 0) return 	FOR;
    if (strcmp(text, "break") 		== 0) return 	BREAK;
    if (strcmp(text, "continue") 	== 0) return 	CONTINUE;
    if (strcmp(text, "pass") 		== 0) return 	PASS;
    if (strcmp(text, "class") 		== 0) return 	CLASS;
    if (strcmp(text, "import") 		== 0) return 	IMPORT;
    if (strcmp(text, "from") 		== 0) return 	FROM;
    if (strcmp(text, "as") 			== 0) return 	AS;
    if (strcmp(text, "try") 		== 0) return 	TRY;
    if (strcmp(text, "except") 		== 0) return 	EXCEPT;
    if (strcmp(text, "finally") 	== 0) return 	FINALLY;
    if (strcmp(text, "with") 		== 0) return 	WITH;
    if (strcmp(text, "lambda") 		== 0) return 	LAMBDA;
    if (strcmp(text, "global") 		== 0) return 	GLOBAL;
    if (strcmp(text, "nonlocal") 	== 0) return 	NONLOCAL;
    if (strcmp(text, "assert") 		== 0) return 	ASSERT;
    if (strcmp(text, "del") 		== 0) return 	DEL;
    if (strcmp(text, "raise") 		== 0) return 	RAISE;
    if (strcmp(text, "yield") 		== 0) return 	YIELD;
    if (strcmp(text, "True") 		== 0) return 	TRUE;
    if (strcmp(text, "False") 		== 0) return 	FALSE;
    if (strcmp(text, "None") 		== 0) return 	NONE;
    if (strcmp(text, "and") 		== 0) return 	AND;
    if (strcmp(text, "or") 			== 0) return 	OR;
    if (strcmp(text, "not") 		== 0) return 	NOT;
    if (strcmp(text, "is") 			== 0) return 	IS;
    if (strcmp(text, "in") 			== 0) return 	IN;
    if (strcmp(text, "async") 		== 0) return 	ASYNC;
    if (strcmp(text, "await")		== 0) return 	AWAIT;
    if (strcmp(text, "+") 			== 0) return 	PLUS;
    if (strcmp(text, "-") 			== 0) return 	MINUS;
    if (strcmp(text, "*") 			== 0) return 	STAR;
    if (strcmp(text, "/") 			== 0) return 	SLASH;
    if (strcmp(text, "//") 			== 0) return 	DOUBLESLASH;
    if (strcmp(text, "%") 			== 0) return 	PERCENT;
    if (strcmp(text, "**") 			== 0) return 	DOUBLESTAR;
    if (strcmp(text, "==") 			== 0) return 	EQ;
    if (strcmp(text, "!=") 			== 0) return 	NEQ;
    if (strcmp(text, "<") 			== 0) return 	LT;
    if (strcmp(text, ">") 			== 0) return 	GT;
    if (strcmp(text, "<=") 			== 0) return 	LTE;
    if (strcmp(text, ">=") 			== 0) return 	GTE;
    if (strcmp(text, "=") 			== 0) return 	ASSIGN;
    if (strcmp(text, "+=") 			== 0) return 	PLUSEQ;
    if (strcmp(text, "-=") 			== 0) return 	MINUSEQ;
    if (strcmp(text, "*=") 			== 0) return 	STAREQ;
    if (strcmp(text, "/=") 			== 0) return 	SLASHEQ;
    if (strcmp(text, "%=") 			== 0) return 	PERCENTEQ;
    if (strcmp(text, "**=") 		== 0) return 	DOUBLESTAREQ;
    if (strcmp(text, "//=") 		== 0) return 	DOUBLESLASHEQ;
    if (strcmp(text, "&") 			== 0) return 	BITAND;
    if (strcmp(text, "|") 			== 0) return 	BITOR;
    if (strcmp(text, "^") 			== 0) return 	BITXOR;
    if (strcmp(text, "~") 			== 0) return 	BITNOT;
    if (strcmp(text, "<<")			== 0) return 	LSHIFT;
    if (strcmp(text, ">>")			== 0) return 	RSHIFT;
    if (strcmp(text, "<<=") 		== 0) return 	LSHIFTEQ;
    if (strcmp(text, ">>=") 		== 0) return 	RSHIFTEQ;
    if (strcmp(text, "&=")			== 0) return 	ANDEQ;
    if (strcmp(text, "|=")			== 0) return 	OREQ;
    if (strcmp(text, "^=")			== 0) return 	XOREQ;
    if (strcmp(text, "(") 			== 0) return 	LPAREN;
    if (strcmp(text, ")") 			== 0) return 	RPAREN;
    if (strcmp(text, "[") 			== 0) return 	LBRACKET;
    if (strcmp(text, "]") 			== 0) return 	RBRACKET;
    if (strcmp(text, "{") 			== 0) return 	LBRACE;
    if (strcmp(text, "}") 			== 0) return 	RBRACE;
    if (strcmp(text, ":") 			== 0) return 	COLON;
    if (strcmp(text, ",") 			== 0) return 	COMMA;
    if (strcmp(text, ".") 			== 0) return 	DOT;
    if (strcmp(text, ";") 			== 0) return 	SEMICOLON;
    if (strcmp(text, "@") 			== 0) return 	AT;
    if (strcmp(text, "->") 			== 0) return 	ARROW;
    if (strcmp(text, "...") 		== 0) return 	ELLIPSIS;
    if (strcmp(text, "\\n") 		== 0) return 	NEWLINE;
    if (strcmp(text, "\t") 			== 0) return 	INDENT;
    if (strcmp(text, "<DEDENT>") 	== 0) return 	DEDENT;
    if (strcmp(text, "<EOF>") 		== 0) return 	EndOF;
    return IDENTIFIER;
}