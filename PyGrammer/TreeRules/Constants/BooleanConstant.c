#define _POSIX_C_SOURCE 200809L/*for strndup*/
#include <PyTree.h>
#include <Nodes.h>
#include <stdlib.h>
#include <string.h>

/*Boolean*/
/*TRUE
  FALSE*/

PyNode
*TreeParseBooleanConstant(PyTreeParser *ParseS)
{
    PyToken *Token = Peek(ParseS);
    if (!Token || (Token->Type != TRUE && Token->Type != FALSE)) return NULL;

    Consume(ParseS);

    PyNode *Node = AllocNode(Pynode_Constant, Token->Line, Token->Column);
    Node->Boolean.Bool = (Token->Type == TRUE);

    return Node;
}