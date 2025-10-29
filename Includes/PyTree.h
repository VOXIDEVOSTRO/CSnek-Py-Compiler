#pragma once

#include <PyTokens.h>

/**
 * TreeParser Structure 
 */
typedef
struct
{

    PyToken *Tokens;
    int Count;
    int Position;
	
}PyTreeParser;

/**
 * Prototypes
 */
PyToken *Peek(PyTreeParser *ParseS);
PyToken *PeekAhead(PyTreeParser *ParseS, int Count);
PyToken *Consume(PyTreeParser *ParseS);
int 	 Match(PyTreeParser *ParseS, PyTokenCat Type);
void 	 ParseError(PyTreeParser *ParseS, const char *ErMessage);
int 	 AtEnd(PyTreeParser *ParseS);