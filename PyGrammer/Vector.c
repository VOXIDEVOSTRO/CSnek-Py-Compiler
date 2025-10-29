/**
 * 
 * Vector Helpers
 * 
 */

#include <NodeVector.h>
#include <stddef.h>
#include <stdlib.h>


void
NodeVectorInit(NodeVector *Vector)
{
    Vector->Items = NULL;
    Vector->Count = 0;
    Vector->Capacity = 0;
}

int
NodeVectorPush(NodeVector *Vector, PyNode *Node)
{
    if (Vector->Count == Vector->Capacity)
	{
        int NewCapacity = Vector->Capacity ? Vector->Capacity * 2 : 8;

        PyNode **NewItems = realloc(Vector->Items, NewCapacity * sizeof(PyNode *));

        if (!NewItems) return 0;
		
        Vector->Items = NewItems;
        Vector->Capacity = NewCapacity;
    }

    Vector->Items[Vector->Count++] = Node;
	
    return 1;
}