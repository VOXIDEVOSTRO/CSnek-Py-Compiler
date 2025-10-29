#define _POSIX_C_SOURCE 200809L/*for strndup*/
#include <PyTree.h>
#include <Nodes.h>
#include <stdlib.h>
#include <string.h>

/*Integer*/
/*n, 1, 2, 67, 69, 420*/

PyNode
*TreeParseIntegerConstant(PyTreeParser *ParseS)
{
    PyToken *Token = Peek(ParseS);
    if (!Token || Token->Type != INTEGER) return NULL; /*Error*/

    Consume(ParseS);

    PyNode *Node = AllocNode(Pynode_Constant, Token->Line, Token->Column);
    Node->Integer.Integer = strtol(Token->Value, NULL, 10);
	
    return Node;
}