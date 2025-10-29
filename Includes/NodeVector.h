#pragma once

#include <Nodes.h>

/**
 * Vector Structure
 */
typedef
struct
{

    PyNode **Items;
    int Count;
    int Capacity;

}NodeVector;

/**
 * Prototypes
 */
int NodeVectorPush(NodeVector *Vector, PyNode *Node);
void NodeVectorInit(NodeVector *Vector);