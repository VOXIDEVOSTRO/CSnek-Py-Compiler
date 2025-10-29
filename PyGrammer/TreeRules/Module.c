#define _POSIX_C_SOURCE 200809L/*for strndup*/
#include <Rules.h>
#include <NodeVector.h>
#include <Main.h>
#include <stdlib.h>
#include <string.h>

/**
 * Main Starting for Parser
 */
PyNode
*TreeParseModule(PyTreeParser *ParseS)
{

#ifdef PyDebugCompiler
    printf("DEBUG: TreeParseModule enter Tokens=%p Count=%d Pos=%d\n",
           (void*)ParseS->Tokens, ParseS->Count, ParseS->Position);
#endif

    PyToken *Start = Peek(ParseS);

#ifdef PyDebugCompiler
    printf("DEBUG: Module start token=%p type=%d line=%d col=%d\n",
           (void*)Start, Start ? Start->Type : -1, Start ? Start->Line : -1, Start ? Start->Column : -1);
#endif

    PyNode *Module = AllocNode(Pynode_Module,
    Start ? Start->Line : 0,
    Start ? Start->Column : 0);

    if (!Module) return NULL;

    PyNode *block = TreeParseBlock(ParseS);
    if (!block)
    {

#ifdef PyDebugCompiler
        ParseError(ParseS, "Failed to parse Module body");
        printf("DEBUG: TreeParseModule block=NULL\n");
#endif

        DeallocNode(Module);

        return NULL;
    }

#ifdef PyDebugCompiler
    printf("DEBUG: TreeParseModule block count=%d items=%p\n",
           block->Block.Count, (void*)block->Block.Statements);
#endif

    /* attach block statements into the Module */
    Module->Block.Statements = block->Block.Statements;
    Module->Block.Count      = block->Block.Count;

#ifdef PyDebugCompiler
    printf("DEBUG: Module after attach count=%d items=%p\n",
           Module->Block.Count, (void*)Module->Block.Statements);
#endif

    /* prevent double free */
    block->Block.Statements = NULL;
    block->Block.Count 		= 0;
    DeallocNode(block);

    if (!AtEnd(ParseS))
    {

#ifdef PyDebugCompiler
        ParseError(ParseS, "Trailing tokens after Module");
        printf("DEBUG: Trailing tokens pos=%d of count=%d\n", ParseS->Position, ParseS->Count);
#endif

    }

#ifdef PyDebugCompiler
    printf("DEBUG: TreeParseModule exit Module=%p\n", (void*)Module);
#endif

    return Module;
}
