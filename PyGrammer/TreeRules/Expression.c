#define _POSIX_C_SOURCE 200809L/*for strndup*/
#include <Rules.h>
#include <Main.h> /* For debug */
#include <stdlib.h>
#include <string.h>

/**
 * Main Expression Caller
 */
PyNode
*TreeParseExpression(PyTreeParser *ParseS)
{

#ifdef PyDebugCompiler
    printf("DEBUG: TreeParseExpression enter Pos=%d\n", ParseS->Position);
#endif

    PyToken *Token = Peek(ParseS);

#ifdef PyDebugCompiler
    printf("DEBUG: Expr token=%p type=%d line=%d col=%d\n",
           (void*)Token, Token ? Token->Type : -1, Token ? Token->Line : -1, Token ? Token->Column : -1);
#endif

    if (!Token) return NULL;

    switch (Token->Type)
    {
        /* Expressions */
        case IDENTIFIER: {

#ifdef PyDebugCompiler
            printf("DEBUG: IDENTIFIER dispatch\n");
#endif

            PyNode *Node = TreeParseNameExpression(ParseS);

#ifdef PyDebugCompiler
            printf("DEBUG: IDENTIFIER result=%p\n", (void*)Node);
#endif

            return Node;
        }

        /* Constants */
        case INTEGER: {

#ifdef PyDebugCompiler
            printf("DEBUG: INTEGER dispatch\n");
#endif

            PyNode *Node = TreeParseIntegerConstant(ParseS);

#ifdef PyDebugCompiler
            printf("DEBUG: INTEGER result=%p\n", (void*)Node);
#endif
            return Node;
        }

        case FLOAT: {

#ifdef PyDebugCompiler
            printf("DEBUG: FLOAT dispatch\n");
#endif

            PyNode *Node = TreeParseFloatConstant(ParseS);

#ifdef PyDebugCompiler
            printf("DEBUG: FLOAT result=%p\n", (void*)Node);
#endif
            return Node;
        }

        case STRING: {

#ifdef PyDebugCompiler
            printf("DEBUG: STRING dispatch\n");
#endif

            PyNode *Node = TreeParseStringConstant(ParseS);

#ifdef PyDebugCompiler
            printf("DEBUG: STRING result=%p\n", (void*)Node);
#endif
            return Node;
        }

        case TRUE:	/*Boolean so just nest it*/
        case FALSE: {

#ifdef PyDebugCompiler
            printf("DEBUG: BOOLEAN dispatch\n");
#endif

            PyNode *Node = TreeParseBooleanConstant(ParseS);

#ifdef PyDebugCompiler
            printf("DEBUG: BOOLEAN result=%p\n", (void*)Node);
#endif
            return Node;
        }

        case NONE: {

#ifdef PyDebugCompiler
            printf("DEBUG: NONE dispatch\n");
#endif

            PyNode *Node = TreeParseNoneConstant(ParseS);

#ifdef PyDebugCompiler
            printf("DEBUG: NONE result=%p\n", (void*)Node);
#endif
            return Node;
        }

        default:

#ifdef PyDebugCompiler
            ParseError(ParseS, "Unexpected token in expression");
            printf("DEBUG: Expr unexpected type=%d at pos=%d\n", Token->Type, ParseS->Position);
#endif

            return NULL;
    }
}
