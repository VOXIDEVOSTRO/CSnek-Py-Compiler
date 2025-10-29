/**
 * 
 * Tree Parser,
 * This will form all grammer for python
 * 
 */

#include <PyTree.h>
#include <Nodes.h>
#include <NodeVector.h>
#include <Main.h>

/**
  * Helpers
  */

/* look at the current token without moving */
PyToken 
*Peek(PyTreeParser *ParseS)
{
    return (ParseS->Position < ParseS->Count) ? &ParseS->Tokens[ParseS->Position] : NULL;
}

 
/* look ahead "Count" tokens without moving */
PyToken 
*PeekAhead(PyTreeParser *ParseS, int Count)
{
    int Index = ParseS->Position + Count;
    return (Index < ParseS->Count) ? &ParseS->Tokens[Index] : NULL;
}

 
/* consume the current token and move */
PyToken
*Consume(PyTreeParser *ParseS)
{
    return (ParseS->Position < ParseS->Count) ? &ParseS->Tokens[ParseS->Position++] : NULL;
}

/* match a specific token type, consuming it if present */ 
int
Match(PyTreeParser *ParseS, PyTokenCat Type)
{
    PyToken *Token = Peek(ParseS);

    if (Token && Token->Type == Type)
	{ 
		Consume(ParseS); return 1;
	}

    return 0;
}


void 
ParseError(PyTreeParser *ParseS, const char *ErMessage)
{
    PyToken *Token = Peek(ParseS);
    int Line = Token ? Token->Line : -1;	/*Error*/
    int Column  = Token ? Token->Column : -1;

#ifdef PyDebugCompiler
    fprintf(stderr, "ParseError at %d:%d: %s\n", Line, Column, ErMessage);
#endif
}

/* check if we are at the end of the token stream */
int 
AtEnd(PyTreeParser *ParseS)
{
    PyToken *Token = Peek(ParseS);

    return !Token || Token->Type == EndOF;
}