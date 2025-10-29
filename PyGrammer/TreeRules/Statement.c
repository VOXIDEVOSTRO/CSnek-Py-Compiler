#define _POSIX_C_SOURCE 200809L/*for strndup*/
#include <Rules.h>
#include <Main.h>
#include <stdlib.h>
#include <string.h>

PyNode
*TreeParseStatement(PyTreeParser *ParseS)
{
#ifdef PyDebugCompiler
    printf("DEBUG: TreeParseStatement enter Pos=%d\n", ParseS->Position);
#endif

    PyToken *Token = Peek(ParseS);

#ifdef PyDebugCompiler
    printf("DEBUG: Statement token=%p type=%d line=%d col=%d\n",
    (void*)Token, Token ? Token->Type : -1, Token ? Token->Line : -1, Token ? Token->Column : -1);
#endif

    if (!Token) return NULL;

    switch (Token->Type)
    {
        case PASS:

#ifdef PyDebugCompiler
            printf("DEBUG: PASS at line=%d col=%d\n", Token->Line, Token->Column);
#endif
            Consume(ParseS);

            return AllocNode(Pynode_Pass, Token->Line, Token->Column);

        case RETURN:
        {

#ifdef PyDebugCompiler
            printf("DEBUG: RETURN at line=%d col=%d\n", Token->Line, Token->Column);
#endif
            Consume(ParseS);

            PyNode *Node = AllocNode(Pynode_Return, Token->Line, Token->Column);

#ifdef PyDebugCompiler
            printf("DEBUG: Return node=%p\n", (void*)Node);
#endif
            if (Peek(ParseS) && Peek(ParseS)->Type != NEWLINE && Peek(ParseS)->Type != EndOF)
            {

#ifdef PyDebugCompiler
                printf("DEBUG: Return has value, parsing expression at pos=%d\n", ParseS->Position);
#endif

                Node->ReturnStatement.Value = TreeParseExpression(ParseS);

#ifdef PyDebugCompiler
                printf("DEBUG: Return value node=%p\n", (void*)Node->ReturnStatement.Value);
#endif
            }

            return Node;
        }

        default:
        {

#ifdef PyDebugCompiler
            printf("DEBUG: Expr statement at pos=%d\n", ParseS->Position);
#endif

            /* expression statement */
            PyNode *Expression = TreeParseExpression(ParseS);

#ifdef PyDebugCompiler
            printf("DEBUG: Expression node=%p\n", (void*)Expression);
#endif

            if (!Expression) return NULL;


            PyNode *Node = AllocNode(Pynode_Expr, Token->Line, Token->Column);
            Node->ExpressionStatement.Value = Expression;

#ifdef PyDebugCompiler
            printf("DEBUG: Expr stmt node=%p value=%p\n",
            (void*)Node, (void*)Node->ExpressionStatement.Value);
#endif

            return Node;
        }
    }
}
