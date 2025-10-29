#define _POSIX_C_SOURCE 200809L/*for strndup*/
#include <PyTree.h>
#include <Nodes.h>
#include <stdlib.h>
#include <string.h>

/*Float*/
/*n.n, 1.2, 6.7, 8.69*/

PyNode
*TreeParseFloatConstant(PyTreeParser *ParseS)
{
    PyToken *Token = Peek(ParseS);
    if (!Token || Token->Type != FLOAT) return NULL;

    Consume(ParseS);

    PyNode *Node = AllocNode(Pynode_Constant, Token->Line, Token->Column);
    Node->Float.Float = strtod(Token->Value, NULL);

    return Node;
}