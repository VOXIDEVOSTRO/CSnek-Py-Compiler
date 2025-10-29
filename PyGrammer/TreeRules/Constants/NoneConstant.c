#define _POSIX_C_SOURCE 200809L/*for strndup*/
#include <PyTree.h>
#include <Nodes.h>
#include <stdlib.h>
#include <string.h>

/*None*/
/*	*/

PyNode
*TreeParseNoneConstant(PyTreeParser *ParseS)
{
    PyToken *Token = Peek(ParseS);
    if (!Token || Token->Type != NONE) return NULL;

    Consume(ParseS);

    PyNode *Node = AllocNode(Pynode_Constant, Token->Line, Token->Column);

    /* nothing to set for None */
    return Node;
}