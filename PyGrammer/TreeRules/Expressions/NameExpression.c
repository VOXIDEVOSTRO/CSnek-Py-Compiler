#define _POSIX_C_SOURCE 200809L/*for strndup*/
#include <PyTree.h>
#include <Nodes.h>
#include <stdlib.h>
#include <string.h>

/**
 * Name an expression from Identifier
 */

PyNode
*TreeParseNameExpression(PyTreeParser *ParseS)
{
    PyToken *Token = Peek(ParseS);
    if (!Token || Token->Type != IDENTIFIER) return NULL;

    Consume(ParseS);
	
    PyNode *Node = AllocNode(Pynode_Name, Token->Line, Token->Column);
    Node->Name.Name = strdup(Token->Value);

    return Node;
}