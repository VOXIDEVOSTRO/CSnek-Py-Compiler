#pragma once

/**
 * Node Types
 * From this list below:
 * https://docs.python.org/3/library/ast.html
 * following Python3
 */
typedef
enum
{
    Pynode_Module,
    Pynode_Interactive,
    Pynode_Expression,
    Pynode_FunctionType,
    Pynode_FunctionDef,
    Pynode_AsyncFunctionDef,
    Pynode_ClassDef,
    Pynode_Return,
    Pynode_Delete,
    Pynode_Assign,
    Pynode_AugAssign,
    Pynode_AnnAssign,
    Pynode_For,
    Pynode_AsyncFor,
    Pynode_While,
    Pynode_If,
    Pynode_With,
    Pynode_AsyncWith,
    Pynode_Match,          /* Python 3.10 structural pattern matching */
    Pynode_Raise,
    Pynode_Try,
    Pynode_Assert,
    Pynode_Import,
    Pynode_ImportFrom,
	Pynode_Block,
    Pynode_Global,
    Pynode_Nonlocal,
    Pynode_Expr,
    Pynode_Pass,
    Pynode_Break,
    Pynode_Continue,
    Pynode_BoolOp,
    Pynode_BinOp,
    Pynode_UnaryOp,
    Pynode_Lambda,
    Pynode_IfExp,
    Pynode_Dict,
    Pynode_Set,
    Pynode_ListComp,
    Pynode_SetComp,
    Pynode_DictComp,
    Pynode_GeneratorExp,
    Pynode_Await,
    Pynode_Yield,
    Pynode_YieldFrom,
    Pynode_Compare,
    Pynode_Call,
    Pynode_FormattedValue,
    Pynode_JoinedStr,
    Pynode_Constant,
    Pynode_Attribute,
    Pynode_Subscript,
    Pynode_Starred,
    Pynode_Name,
    Pynode_List,
    Pynode_Tuple,
    Pynode_Slice,
    Pynode_Add,
    Pynode_Sub,
    Pynode_Mult,
    Pynode_MatMult,
    Pynode_Div,
    Pynode_Mod,
    Pynode_Pow,
    Pynode_LShift,
    Pynode_RShift,
    Pynode_BitOr,
    Pynode_BitXor,
    Pynode_BitAnd,
    Pynode_FloorDiv,
    Pynode_Invert,
    Pynode_Not,
    Pynode_UAdd,
    Pynode_USub,
    Pynode_And,
    Pynode_Or,
    Pynode_Eq,
    Pynode_NotEq,
    Pynode_Lt,
    Pynode_LtE,
    Pynode_Gt,
    Pynode_GtE,
    Pynode_Is,
    Pynode_IsNot,
    Pynode_In,
    Pynode_NotIn,
    Pynode_comprehension,   /* for list/set/dict/generator comprehensions */
    Pynode_arguments,       /* function arguments 						  */
    Pynode_arg,             /* single argument 							  */
    Pynode_keyword,         /* keyword argument in call 				  */
    Pynode_alias,           /* import alias 							  */
    Pynode_withitem,        /* with statement item 						  */
    Pynode_match_case,      /* match/case 								  */
    Pynode_pattern,         /* pattern matching 						  */
    Pynode_match_value,
    Pynode_match_singleton,
    Pynode_match_sequence,
    Pynode_match_mapping,
    Pynode_match_class,
    Pynode_match_star,
    Pynode_match_as,
    Pynode_match_or

}PyTypeNodes;

/**
 * Main Node Structure
 * NodeTree?
 * TODO: Give it a proper name ig
 */
typedef struct 
PyNode PyNode;
struct 
PyNode
{
    PyTypeNodes Kind;
    int Line;           
    int Column;

    union
	{
		/*Types*/
        struct 
		{ 
			char *Name; 
		} Name;  
        struct
		{ 
			long Integer; 
		} Integer;
        struct
		{ 
			double Float;
		} Float;  
        struct
		{ 
			char *String; 
		} String;
        struct
		{ 
			int Bool;
		} Boolean; 
        struct
		{ 

		} None;              

		/*Nodes*/
        struct 
		{ 
			PyNode *Left, *Right; 
			PyTypeNodes Operation; 
		} BinaryOperation;
        struct 
		{ 
			PyNode *Operand; 
			PyTypeNodes Operation; 
		} Unary;
        struct 
		{ 
			PyNode *Function; 
			PyNode **Arguments; 
			int ArgumentsCount; 
			PyNode **KeyWords; 
			int KeyWordsCount; 
		} Call;
        struct 
		{ 
			PyNode *Value;
			char *Attribute; 
		} Attribute;
        struct 
		{ 
			PyNode *Value;
			PyNode *Slice; 
		} SubScript;
        struct 
		{ 
			PyNode **Elements; 
			int Count; 
		} List;
        struct 
		{ 
			PyNode **Elements; 
			int Count; 
		} Tuple;
        struct 
		{ 
			PyNode **Keys;
			PyNode **Values;
			int Count;
		} Dictionary;
        struct 
		{ 
			PyNode **Elements;
			int Count;
		} Set;
        struct 
		{ 
			PyNode *Test, *Body, *OrElse; 
		} IfExpression;
        struct 
		{ 
			PyNode *Generators;
			PyNode *Elements; 
		} Comprehension;
        struct 
		{ 
			char *Name; 
			PyNode *Arguments; 
			PyNode *Body; 
			PyNode *Decorators;
		} FunctionDef;
        struct 
		{ 
			char *Name; 
			PyNode *Bases; 
			PyNode *Body; 
			PyNode *Decorators;
		} ClassDef;
        struct 
		{ 
			PyNode *Value;
		} ExpressionStatement;
        struct 
		{ 
			PyNode *Targets; 
			PyNode *Value; 
		} Assign;
        struct 
		{ 
			PyNode *Target; 
			PyTypeNodes Operator; 
			PyNode *Value; 
		} AugumnetAssign;
        struct 
		{ 
			PyNode *Target;
			PyNode *Annotation;
			PyNode *Value;
		} AnnoteAssign;
        struct 
		{ 
			PyNode *Test;
			PyNode *Body;
			PyNode *OrElse;
		} IfStatement;
        struct 
		{ 
			PyNode *Test; 
			PyNode *Body;
		} WhileStatement;
        struct 
		{ 
			PyNode *Target; 
			PyNode *Iteration; 
			PyNode *Body; 
			PyNode *OrElse; 
		} ForStatement;
        struct 
		{ 
			PyNode *Items; 
			PyNode *Body; 
		} WithStatement;
        struct 
		{ 
			PyNode *Exception; 
			PyNode *Cause; 
		} Raise;
        struct 
		{ 
			PyNode *Body; 
			PyNode *Handlers; 
			PyNode *OrElse; 
			PyNode *FinalBody; 
		} TryStatement;
        struct 
		{ 
			PyNode *Test; 
			PyNode *Message; 
		} AssertStatement;
        struct 
		{ 
			/* Useful for our LowPyLibrary */
			PyNode *Names;
		} ImportStatement;
        struct 
		{ 
			/* Same as Above */
			PyNode *Module; 
			PyNode *Names; 
			int Level; 
		} ImportFrom;
        struct 
		{ 
			PyNode *Value; 
		} ReturnStatement;
        struct 
		{ 
			PyNode *Value; 
		} YieldStatement;
        struct 
		{ 
			PyNode *Value; 
		} YieldFrom;
        struct 
		{ 
			PyNode *Subject; 
			PyNode *Cases; 
		} MatchStatement;
        struct 
		{ 
			PyNode *Pattern; 
			PyNode *Guard; 
			PyNode *Body; 
		} MatchCase;
        struct 
		{ 
			PyNode *Value; 
		} MatchValue;
        struct 
		{ 
			char *Identity; 
		} MatchSingleton;
        struct 
		{ 
			PyNode **Patterns; 
			int Count; 
		} MatchSequence;
        struct 
		{ 
			PyNode **Keys; 
			PyNode **Patterns; 
			int Count; 
		} MatchMapping;
        struct 
		{ 
			PyNode *Class; 
			PyNode **Patterns; 
			int Count; 
		} MatchClass;
        struct 
		{ 
			char *Name; 
		} MatchStar;
        struct 
		{ 
			char *Name; 
			PyNode *Pattern; 
		} MatchAs;
        struct 
		{ 
			PyNode **Patterns; 
			int Count; 
		} MatchOr;
		struct
        {
            PyNode *Arguments;
            PyNode *Body;
        } Lambda;
		struct
        {
            PyNode *Left;
            PyNode **Comparators;
            int Count;
            PyTypeNodes *Operators;
        } Compare;
		struct
        {
            PyNode *Value;
            int Conversion;
            PyNode *FormatSpec;
        } FormattedValue;
		struct
        {
            PyNode **Values;
            int Count;
        } JoinedString;
		struct
        {
            PyNode *Value;
        } Starred;
		struct
        {
			/* NULL */
            PyNode *Lower;
            PyNode *Upper;
            PyNode *Step;
        } Slice;
		struct
        {
            PyNode **Arguments;
            int Count;
        } Arguments;
		struct
        {
            char *ArgumentName;
            PyNode *Annotation;
        } Argument;
		struct
        {
            char *Name;
            PyNode *Value;
        } KeyWord;
		struct
        {
            char *Name;
            char *AliasName;
        } Alias;
		struct
        {
            PyNode *ContextExpression;
            PyNode *OptionalVariables;
        } WithItem;
		struct
        {
            PyNode *Value;
        } Await;
		struct
        {
            PyNode *Targets;
        } Delete;
		struct
        {
            PyNode **Names;
            int Count;
        } Global;
		struct
        {
            PyNode **Names;
            int Count;
        } NonLocal;
		struct
        {
            PyNode *Generators;
            PyNode *Element;
        } ListComprehension;
		struct
        {
            PyNode *Generators;
            PyNode *Element;
        } SetComprehension;
        struct
        {
            PyNode *Generators;
            PyNode *Key;
            PyNode *Value;
        } DictionaryComprehension;
		struct
        {
            PyNode *Generators;
            PyNode *Element;
        } GeneratorExpression;
        struct 
		{ 
			PyNode **Statements; 
			int Count; 
		} Block;   /* generic block */
    };
};

/**
 * Prototypes
 */
/*Nodes.c*/
void DeallocNode(PyNode *Node);
PyNode *AllocNode(PyTypeNodes TypeNode, int Line, int Column);