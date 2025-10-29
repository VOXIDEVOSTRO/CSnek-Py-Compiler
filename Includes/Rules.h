#pragma once
#include <PyTree.h>
#include <Nodes.h>

/**
 * Prototypes
 */

/*
	Constants/
*/
PyNode *TreeParseBooleanConstant(PyTreeParser *ParseS);
PyNode *TreeParseFloatConstant(PyTreeParser *ParseS);
PyNode *TreeParseIntegerConstant(PyTreeParser *ParseS);
PyNode *TreeParseNoneConstant(PyTreeParser *ParseS);
PyNode *TreeParseStringConstant(PyTreeParser *ParseS);

/*
	Expressions/
*/
PyNode *TreeParseNameExpression(PyTreeParser *ParseS);

/*
	Mains
*/
PyNode *TreeParseStatement(PyTreeParser *ParseS);
PyNode *TreeParseBlock(PyTreeParser *ParseS);
PyNode *TreeParseModule(PyTreeParser *ParseS);
PyNode *TreeParseExpression(PyTreeParser *ParseS);