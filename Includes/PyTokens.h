#pragma once
#include <stdio.h>
/**
 * Enum For Token Class
 */
typedef
enum 
{

    DEF,
    RETURN,
    IF,
    ELSE,
    ELIF,
    WHILE,
    FOR,
    BREAK,
    CONTINUE,
    PASS,
    CLASS,
    IMPORT,
    FROM,
    AS,
    TRY,
    EXCEPT,
    FINALLY,
    WITH,
    LAMBDA,
    GLOBAL,
    NONLOCAL,
    ASSERT,
    DEL,
    RAISE,
    YIELD,
    TRUE,
    FALSE,
    NONE,
    AND,
    OR,
    NOT,
    IS,
    IN,
    ASYNC,
    AWAIT,
    IDENTIFIER,
    INTEGER,
    FLOAT,
    STRING,     /* "..." or '...' */
    FSTRING,    /* f"..." or F"..." */
    RSTRING,    /* r"..." or R"..." */
    FRSTRING,   /* fr"..." or rf"..." */
    BYTES,      /* b"..." or B"..." */
    RBSTRING,   /* rb"..." or br"..." */
    USTRING,    /* u"..." legacy */
    PLUS,         /* +	*/
    MINUS,        /* -	*/
    STAR,         /* *	*/
    SLASH,        /* /	*/
    DOUBLESLASH,  /* //	*/
    PERCENT,      /* %	*/
    DOUBLESTAR,   /* ** */
    EQ,           /* ==	*/
    NEQ,          /* !=	*/
    LT,           /* <	*/
    GT,           /* >	*/
    LTE,          /* <=	*/
    GTE,          /* >=	*/
    ASSIGN,       /* =	*/
    PLUSEQ,       /* +=	*/
    MINUSEQ,      /* -=	*/
    STAREQ,       /* *=	*/
    SLASHEQ,      /* /=	*/
    PERCENTEQ,    /* %=	*/
    DOUBLESTAREQ, /* **=*/
    DOUBLESLASHEQ,/* //=*/
    BITAND,       /* &	*/
    BITOR,        /* |	*/
    BITXOR,       /* ^	*/
    BITNOT,       /* ~	*/
    LSHIFT,       /* <<	*/
    RSHIFT,       /* >>	*/
    LSHIFTEQ,     /* <<=*/
    RSHIFTEQ,     /* >>=*/
    ANDEQ,        /* &=	*/
    OREQ,         /* |=	*/
    XOREQ,        /* ^=	*/
    NOTEQ,        /* !=	*/
    LPAREN,       /* (	*/
    RPAREN,       /* )	*/
    LBRACKET,     /* [	*/
    RBRACKET,     /* ]	*/
    LBRACE,       /* {	*/
    RBRACE,       /* }	*/
    COLON,        /* :	*/
    COMMA,        /* ,	*/
    DOT,          /* .	*/
    SEMICOLON,    /* ;	*/
    AT,           /* @	*/
    ARROW,        /* ->	*/
    ELLIPSIS,     /* ...*/
    NEWLINE,
    INDENT,
    DEDENT,
    EndOF,

}PyTokenCat;

/**
 * Main Token
 */
typedef
struct
{

    PyTokenCat Type;
    char 	   *Value;
    int 	   Line;
    int 	   Column;

}PyToken;

/**
 * Token List
 */
#define LimToken 2048
typedef
struct
{

    PyToken Tokens[LimToken];
    int Count;

}PyTokenList;

/**
 * Prototypes
 */
/*Tokens.c*/
PyTokenCat MirrorCheckToken(const char *text);
/*Lexer.c*/
void Emit(PyTokenList *Output, PyTokenCat TokenClass, const char *Lexeme, int EmitLine, int EmitColumn);
void LexOutFile(FILE *File, PyTokenList *Output);