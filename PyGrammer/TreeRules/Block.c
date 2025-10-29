#define _POSIX_C_SOURCE 200809L/*for strndup*/
#include <Rules.h>
#include <NodeVector.h>
#include <Main.h>
#include <stdlib.h>
#include <string.h>

PyNode
*TreeParseBlock(PyTreeParser *ParseS)
{

#ifdef PyDebugCompiler
    printf("DEBUG: TreeParseBlock enter Pos=%d Count=%d\n", ParseS->Position, ParseS->Count);
#endif

    PyToken *Start = Peek(ParseS);

#ifdef PyDebugCompiler
    printf("DEBUG: Block start token=%p type=%d line=%d col=%d\n",
    (void*)Start, Start ? Start->Type : -1, Start ? Start->Line : -1, Start ? Start->Column : -1);
#endif

    PyNode *Block = AllocNode(Pynode_Block,
    Start ? Start->Line : 0,
    Start ? Start->Column : 0);

    if (!Block) return NULL;

    NodeVector StmtVec;
    NodeVectorInit(&StmtVec);

#ifdef PyDebugCompiler
    printf("DEBUG: NV init items=%p count=%d cap=%d\n",
    (void*)StmtVec.Items, StmtVec.Count, StmtVec.Capacity);
#endif

    while (!AtEnd(ParseS))
    {
        /* stop if we see a DEDENT (for indented suites later) */
        if (Peek(ParseS) && Peek(ParseS)->Type == DEDENT)
        {

#ifdef PyDebugCompiler
            printf("DEBUG: Saw DEDENT at pos=%d\n", ParseS->Position);
#endif
            Consume(ParseS);
            break;
        }

        /* skip stray newlines */
        if (Match(ParseS, NEWLINE))
		{

#ifdef PyDebugCompiler
            printf("DEBUG: Skipped NEWLINE at pos now=%d\n", ParseS->Position);
#endif
            continue;
        }

        PyNode *StmtNode = TreeParseStatement(ParseS);

#ifdef PyDebugCompiler
        printf("DEBUG: Statement node=%p pos=%d\n", (void*)StmtNode, ParseS->Position);
#endif

        if (!StmtNode)
        {

#ifdef PyDebugCompiler
            ParseError(ParseS, "Failed to parse statement");
            printf("DEBUG: Breaking block due to NULL statement\n");
#endif
            break;
        }

        if (!NodeVectorPush(&StmtVec, StmtNode))
        {

#ifdef PyDebugCompiler
            ParseError(ParseS, "Out of memory pushing statement");
            printf("DEBUG: NV push failed items=%p count=%d cap=%d\n",
            (void*)StmtVec.Items, StmtVec.Count, StmtVec.Capacity);
#endif
            DeallocNode(StmtNode);
            break;
        }

#ifdef PyDebugCompiler
        printf("DEBUG: NV after push items=%p count=%d cap=%d last=%p\n",
        (void*)StmtVec.Items, StmtVec.Count, StmtVec.Capacity,
        StmtVec.Items ? (void*)StmtVec.Items[StmtVec.Count-1] : NULL);
#endif

        /* consume optional newline after statement */
        if (Peek(ParseS) && Peek(ParseS)->Type == NEWLINE)
		{
            Consume(ParseS);

#ifdef PyDebugCompiler
            printf("DEBUG: Consumed trailing NEWLINE pos=%d\n", ParseS->Position);
#endif
        }
    }

    Block->Block.Count      = StmtVec.Count;
    Block->Block.Statements = StmtVec.Items;

#ifdef PyDebugCompiler
    printf("DEBUG: TreeParseBlock exit Block=%p count=%d items=%p\n",
    (void*)Block, Block->Block.Count, (void*)Block->Block.Statements);
#endif

    return Block;
}
