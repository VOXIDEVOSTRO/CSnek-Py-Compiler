#include <stdlib.h>
#include <string.h>
#include <Nodes.h>
#include <Main.h>
#include <stdio.h>

/**
 * Allocate Node
 */
PyNode *AllocNode(PyTypeNodes TypeNode, int Line, int Column)
{
    /* Allocate a Node */
    PyNode *Node = malloc(sizeof(PyNode));

    if (Node)
    {
        memset(Node, 0, sizeof(*Node));

        /* Initialize the Node */
        Node->Kind   = TypeNode;
        Node->Line   = Line;
        Node->Column = Column;
#ifdef PyDebugCompiler
        printf("DEBUG: AllocNode kind=%d line=%d col=%d ptr=%p\n",
               TypeNode, Line, Column, (void*)Node);
#endif
    }
#ifdef PyDebugCompiler
    else {
        printf("DEBUG: AllocNode failed malloc for kind=%d\n", TypeNode);
    }
#endif

    return Node;
}

/**
 * Deallocate/Free A Node
 * Recursive
 */
void 
DeallocNode(PyNode *Node)
{
    if (!Node) 
	return;

    switch (Node->Kind)
	{
        case Pynode_Name:
            free(Node->Name.Name);
            break;

        case Pynode_Constant:
            /* no owned memory for constant beyond primitive fields */
            break;

        /* expressions */
        case Pynode_BinOp:

            DeallocNode(Node->BinaryOperation.Left);
            DeallocNode(Node->BinaryOperation.Right);
            break;

        case Pynode_BoolOp:

            DeallocNode(Node->BinaryOperation.Left);
            DeallocNode(Node->BinaryOperation.Right);
            break;

        case Pynode_UnaryOp:

            DeallocNode(Node->Unary.Operand);
            break;

        case Pynode_Call:

            DeallocNode(Node->Call.Function);
            if (Node->Call.Arguments)
			{
                for (int Iteration = 0; Iteration < Node->Call.ArgumentsCount; Iteration++)

                    DeallocNode(Node->Call.Arguments[Iteration]);

                free(Node->Call.Arguments);
            }
            if (Node->Call.KeyWords)
			{
                for (int Iteration = 0; Iteration < Node->Call.KeyWordsCount; Iteration++)

                    DeallocNode(Node->Call.KeyWords[Iteration]);

                free(Node->Call.KeyWords);
            }
            break;

        case Pynode_Attribute:

            DeallocNode(Node->Attribute.Value);
            free(Node->Attribute.Attribute);
            break;

        case Pynode_Subscript:

            DeallocNode(Node->SubScript.Value);
            DeallocNode(Node->SubScript.Slice);
            break;

        case Pynode_List:

            if (Node->List.Elements)
			{
                for (int Iteration = 0; Iteration < Node->List.Count; Iteration++)

                    DeallocNode(Node->List.Elements[Iteration]);

                free(Node->List.Elements);
            }
            break;

        case Pynode_Tuple:

            if (Node->Tuple.Elements)
			{
                for (int Iteration = 0; Iteration < Node->Tuple.Count; Iteration++)

                    DeallocNode(Node->Tuple.Elements[Iteration]);

                free(Node->Tuple.Elements);
            }
            break;

        case Pynode_Dict:

            if (Node->Dictionary.Keys)
			{
                for (int Iteration = 0; Iteration < Node->Dictionary.Count; Iteration++)

                    DeallocNode(Node->Dictionary.Keys[Iteration]);

                free(Node->Dictionary.Keys);
            }
            if (Node->Dictionary.Values)
			{
                for (int Iteration = 0; Iteration < Node->Dictionary.Count; Iteration++)

                    DeallocNode(Node->Dictionary.Values[Iteration]);

                free(Node->Dictionary.Values);
            }
            break;

        case Pynode_Set:

            if (Node->Set.Elements)
			{
                for (int Iteration = 0; Iteration < Node->Set.Count; Iteration++)

                    DeallocNode(Node->Set.Elements[Iteration]);

                free(Node->Set.Elements);
            }
            break;

        case Pynode_IfExp:

            DeallocNode(Node->IfExpression.Test);
            DeallocNode(Node->IfExpression.Body);
            DeallocNode(Node->IfExpression.OrElse);
            break;

        case Pynode_comprehension:

            DeallocNode(Node->Comprehension.Generators);
            DeallocNode(Node->Comprehension.Elements);
            break;

        case Pynode_Lambda:

            DeallocNode(Node->Lambda.Arguments);
            DeallocNode(Node->Lambda.Body);
            break;

        case Pynode_Compare:

            DeallocNode(Node->Compare.Left);
            if (Node->Compare.Comparators)
			{
                for (int Iteration = 0; Iteration < Node->Compare.Count; Iteration++)
                    DeallocNode(Node->Compare.Comparators[Iteration]);
                free(Node->Compare.Comparators);
            }
            if (Node->Compare.Operators)
			{
                free(Node->Compare.Operators);
            }
            break;

        case Pynode_FormattedValue:

            DeallocNode(Node->FormattedValue.Value);
            DeallocNode(Node->FormattedValue.FormatSpec);
            break;

        case Pynode_JoinedStr:

            if (Node->JoinedString.Values)
			{
                for (int Iteration = 0; Iteration < Node->JoinedString.Count; Iteration++)

                    DeallocNode(Node->JoinedString.Values[Iteration]);

                free(Node->JoinedString.Values);
            }
            break;

        case Pynode_Starred:

            DeallocNode(Node->Starred.Value);
            break;

        case Pynode_Slice:

            DeallocNode(Node->Slice.Lower);
            DeallocNode(Node->Slice.Upper);
            DeallocNode(Node->Slice.Step);
            break;

        case Pynode_Await:

            DeallocNode(Node->Await.Value);
            break;

        /* Statements */

        case Pynode_Expr:

            DeallocNode(Node->ExpressionStatement.Value);
            break;

        case Pynode_Assign:

            DeallocNode(Node->Assign.Targets);
            DeallocNode(Node->Assign.Value);
            break;

        case Pynode_AugAssign:

            DeallocNode(Node->AugumnetAssign.Target);
            DeallocNode(Node->AugumnetAssign.Value);
            break;

        case Pynode_AnnAssign:

            DeallocNode(Node->AnnoteAssign.Target);
            DeallocNode(Node->AnnoteAssign.Annotation);
            DeallocNode(Node->AnnoteAssign.Value);
            break;

        case Pynode_If:

            DeallocNode(Node->IfStatement.Test);
            DeallocNode(Node->IfStatement.Body);
            DeallocNode(Node->IfStatement.OrElse);
            break;

        case Pynode_While:

            DeallocNode(Node->WhileStatement.Test);
            DeallocNode(Node->WhileStatement.Body);
            break;

        case Pynode_For:
        case Pynode_AsyncFor:
            DeallocNode(Node->ForStatement.Target);
            DeallocNode(Node->ForStatement.Iteration);
            DeallocNode(Node->ForStatement.Body);
            DeallocNode(Node->ForStatement.OrElse);
            break;

        case Pynode_With:

        case Pynode_AsyncWith:

            DeallocNode(Node->WithStatement.Items);
            DeallocNode(Node->WithStatement.Body);
            break;

        case Pynode_Raise:

            DeallocNode(Node->Raise.Exception);
            DeallocNode(Node->Raise.Cause);
            break;

        case Pynode_Try:

            DeallocNode(Node->TryStatement.Body);
            DeallocNode(Node->TryStatement.Handlers);
            DeallocNode(Node->TryStatement.OrElse);
            DeallocNode(Node->TryStatement.FinalBody);
            break;

        case Pynode_Assert:

            DeallocNode(Node->AssertStatement.Test);
            DeallocNode(Node->AssertStatement.Message);
            break;

        case Pynode_Import:

            DeallocNode(Node->ImportStatement.Names);
            break;

        case Pynode_ImportFrom:

            DeallocNode(Node->ImportFrom.Module);
            DeallocNode(Node->ImportFrom.Names);
            /* level is an int, nothing to free */
            break;

        case Pynode_Return:

            DeallocNode(Node->ReturnStatement.Value);
            break;

        case Pynode_Yield:

            DeallocNode(Node->YieldStatement.Value);
            break;

        case Pynode_YieldFrom:

            DeallocNode(Node->YieldFrom.Value);
            break;

        case Pynode_FunctionDef:

        case Pynode_AsyncFunctionDef:

            free(Node->FunctionDef.Name);
            DeallocNode(Node->FunctionDef.Arguments);
            DeallocNode(Node->FunctionDef.Body);
            DeallocNode(Node->FunctionDef.Decorators);
            break;

        case Pynode_ClassDef:
		
            free(Node->ClassDef.Name);
            DeallocNode(Node->ClassDef.Bases);
            DeallocNode(Node->ClassDef.Body);
            DeallocNode(Node->ClassDef.Decorators);
            break;

        case Pynode_Delete:

            DeallocNode(Node->Delete.Targets);
            break;

        case Pynode_Global:

            if (Node->Global.Names)
			{
                for (int Iteration = 0; Iteration < Node->Global.Count; Iteration++)

                    DeallocNode(Node->Global.Names[Iteration]);

                free(Node->Global.Names);
            }
            break;

        case Pynode_Nonlocal:

            if (Node->NonLocal.Names)
			{
                for (int Iteration = 0; Iteration < Node->NonLocal.Count; Iteration++)

                    DeallocNode(Node->NonLocal.Names[Iteration]);

                free(Node->NonLocal.Names);
            }
            break;

        /* comprehensions */

        case Pynode_ListComp:

            DeallocNode(Node->ListComprehension.Generators);
            DeallocNode(Node->ListComprehension.Element);
            break;

        case Pynode_SetComp:

            DeallocNode(Node->SetComprehension.Generators);
            DeallocNode(Node->SetComprehension.Element);
            break;

        case Pynode_DictComp:

            DeallocNode(Node->DictionaryComprehension.Generators);
            DeallocNode(Node->DictionaryComprehension.Key);
            DeallocNode(Node->DictionaryComprehension.Value);
            break;

        case Pynode_GeneratorExp:

            DeallocNode(Node->GeneratorExpression.Generators);
            DeallocNode(Node->GeneratorExpression.Element);
            break;

        /* match / pattern */

        case Pynode_Match:

            DeallocNode(Node->MatchStatement.Subject);
            DeallocNode(Node->MatchStatement.Cases);
            break;

        case Pynode_match_case:

            DeallocNode(Node->MatchCase.Pattern);
            DeallocNode(Node->MatchCase.Guard);
            DeallocNode(Node->MatchCase.Body);
            break;

        case Pynode_match_value:

            DeallocNode(Node->MatchValue.Value);
            break;

        case Pynode_match_singleton:

            free(Node->MatchSingleton.Identity);
            break;

        case Pynode_match_sequence:

            if (Node->MatchSequence.Patterns)
			{
                for (int Iteration = 0; Iteration < Node->MatchSequence.Count; Iteration++)

                    DeallocNode(Node->MatchSequence.Patterns[Iteration]);

                free(Node->MatchSequence.Patterns);
            }
            break;

        case Pynode_match_mapping:

            if (Node->MatchMapping.Keys)
			{
                for (int Iteration = 0; Iteration < Node->MatchMapping.Count; Iteration++)

                    DeallocNode(Node->MatchMapping.Keys[Iteration]);

                free(Node->MatchMapping.Keys);
            }
            if (Node->MatchMapping.Patterns)
			{
                for (int Iteration = 0; Iteration < Node->MatchMapping.Count; Iteration++)

                    DeallocNode(Node->MatchMapping.Patterns[Iteration]);

                free(Node->MatchMapping.Patterns);
            }
            break;

        case Pynode_match_class:

            DeallocNode(Node->MatchClass.Class);
            if (Node->MatchClass.Patterns)
			{
                for (int Iteration = 0; Iteration < Node->MatchClass.Count; Iteration++)

                    DeallocNode(Node->MatchClass.Patterns[Iteration]);

                free(Node->MatchClass.Patterns);
            }
            break;

        case Pynode_match_star:

            free(Node->MatchStar.Name);
            break;

        case Pynode_match_as:

            free(Node->MatchAs.Name);
            DeallocNode(Node->MatchAs.Pattern);
            break;

        case Pynode_match_or:

            if (Node->MatchOr.Patterns) {
                for (int Iteration = 0; Iteration < Node->MatchOr.Count; Iteration++)
                    DeallocNode(Node->MatchOr.Patterns[Iteration]);
                free(Node->MatchOr.Patterns);
            }
            break;

        /* arguments/arg/keyword/alias/withitem */
        case Pynode_arguments:

            if (Node->Arguments.Arguments)
			{
                for (int Iteration = 0; Iteration < Node->Arguments.Count; Iteration++)

                    DeallocNode(Node->Arguments.Arguments[Iteration]);

                free(Node->Arguments.Arguments);
            }
            break;

        case Pynode_arg:

            free(Node->Argument.ArgumentName);
            DeallocNode(Node->Argument.Annotation);
            break;

        case Pynode_keyword:

            free(Node->KeyWord.Name);
            DeallocNode(Node->KeyWord.Value);
            break;

        case Pynode_alias:

            free(Node->Alias.Name);
            free(Node->Alias.AliasName);
            break;

        case Pynode_withitem:

            DeallocNode(Node->WithItem.ContextExpression);
            DeallocNode(Node->WithItem.OptionalVariables);
            break;

        /* module/interactive/expression (block payload) */
        case Pynode_Module:

        case Pynode_Interactive:

        case Pynode_Expression:

        case Pynode_Block:

            if (Node->Block.Statements)
			{
                for (int Iteration = 0; Iteration < Node->Block.Count; Iteration++)

                    DeallocNode(Node->Block.Statements[Iteration]);

                free(Node->Block.Statements);
            }
            break;

        /* operators and tags (no owned payload) */
        case Pynode_Add: 		case Pynode_Sub: 	case Pynode_Mult: 	case Pynode_MatMult:

        case Pynode_Div: 		case Pynode_Mod: 	case Pynode_Pow:

        case Pynode_LShift: 	case Pynode_RShift:

        case Pynode_BitOr: 		case Pynode_BitXor: case Pynode_BitAnd:

        case Pynode_FloorDiv:

        case Pynode_Invert: 	case Pynode_Not: 	case Pynode_UAdd: 	case Pynode_USub:

        case Pynode_And: 		case Pynode_Or:

        case Pynode_Eq: 		case Pynode_NotEq: 	case Pynode_Lt: 	case Pynode_LtE:

        case Pynode_Gt: 		case Pynode_GtE: 	case Pynode_Is: 	case Pynode_IsNot:

        case Pynode_In: 		case Pynode_NotIn:
            break;

        /* unimplimented? */

        case Pynode_FunctionType:

        case Pynode_Pass:

        case Pynode_Break:

        case Pynode_Continue:

        case Pynode_pattern:
		
            /* nope */
            break;

        default:
            break;
    }

    free(Node);
}