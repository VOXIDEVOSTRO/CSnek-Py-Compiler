#define _POSIX_C_SOURCE 200809L/*for strndup*/
#include <PyTree.h>
#include <Nodes.h>
#include <stdlib.h>
#include <string.h>

/*Strings*/
/*'single', "double", """triple"""*/

PyNode 
*TreeParseStringConstant(PyTreeParser *ParseS)
{
    PyToken *Token = Peek(ParseS);
    if (!Token || Token->Type != STRING) return NULL;

    Consume(ParseS);

    PyNode *Node = AllocNode(Pynode_Constant, Token->Line, Token->Column);
    Node->String.String = strdup(Token->Value);

    return Node;
}