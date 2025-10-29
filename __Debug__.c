#include <__Debug__.h>
#include <Nodes.h>
#include <stdio.h>

/**
 * 
 * Tree Debug Helper
 * 
 */

void
PrintAST(PyNode *Node, int Indent)
{

#ifdef PyDebugCompiler
    printf("DEBUG: PrintAST enter Node=%p indent=%d\n", (void*)Node, Indent);
#endif

    if (!Node) return;

    for (int Iteration = 0; Iteration < Indent; Iteration++) printf("  ");
    printf("Node kind: %d (line %d, col %d)\n", Node->Kind, Node->Line, Node->Column);

    switch (Node->Kind)
    {
        case Pynode_Name:

#ifdef PyDebugCompiler
            printf("DEBUG: Name node ptr=%p str=%p\n", (void*)Node, (void*)Node->Name.Name);
#endif

            for (int Iteration = 0; Iteration < Indent+1; Iteration++) printf("  ");
            printf("Name: %s\n", Node->Name.Name ? Node->Name.Name : "<null>");
            break;

        case Pynode_Constant:

#ifdef PyDebugCompiler
		    printf("DEBUG: Constant node kind=%d int=%ld str_ptr=%p bool=%d\n",
		    Node->Kind,
		    Node->Integer.Integer,
		    (void*)Node->String.String,
		    Node->Boolean.Bool);
#endif
			/*TODO: Extend this ig to give more information*/
		    for (int Iteration = 0; Iteration < Indent+1; Iteration++) printf("  ");
		    printf("Constant (int=%ld, str_ptr=%p, bool=%d)\n",
		    Node->Integer.Integer,
		    (void*)Node->String.String,
		    Node->Boolean.Bool);
		    break;

        case Pynode_Block:
        case Pynode_Module:

#ifdef PyDebugCompiler
            printf("DEBUG: Block/Module start count=%d items=%p\n",
                   Node->Block.Count, (void*)Node->Block.Statements);
#endif

            if (Node->Block.Count > 0 && Node->Block.Statements == NULL)
            {
                printf("  [ERROR: Block.Count=%d but Statements=NULL]\n", Node->Block.Count);
                break;
            }

            for (int Iteration = 0; Iteration < Node->Block.Count; Iteration++)
            {

#ifdef PyDebugCompiler
                printf("DEBUG: child[%d] ptr=%p\n", Iteration,
                (void*)(Node->Block.Statements ? Node->Block.Statements[Iteration] : NULL));
#endif

                if (!Node->Block.Statements[Iteration])
                {
                    printf("  [WARNING: NULL child at %d]\n", Iteration);
                    continue;
                }
                PrintAST(Node->Block.Statements[Iteration], Indent+1);
            }

#ifdef PyDebugCompiler
            printf("DEBUG: Block/Module end\n");
#endif
            break;

        case Pynode_Expr:

#ifdef PyDebugCompiler
            printf("DEBUG: Expr child ptr=%p\n", (void*)Node->ExpressionStatement.Value);
#endif
            PrintAST(Node->ExpressionStatement.Value, Indent+1);
            break;

        case Pynode_Return:

#ifdef PyDebugCompiler

            printf("DEBUG: Return child ptr=%p\n", (void*)Node->ReturnStatement.Value);
#endif
            PrintAST(Node->ReturnStatement.Value, Indent+1);
            break;

        default:

#ifdef PyDebugCompiler
            printf("DEBUG: Unhandled kind=%d\n", Node->Kind);
#endif
            break;
    }

#ifdef PyDebugCompiler
    printf("DEBUG: PrintAST exit Node=%p\n", (void*)Node);
#endif

}