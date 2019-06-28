#include "stdafx.h"
#include "AABBTree.h"

AABBTree::AABBTree()
{
}

void AABBTree::syncHierarchy(int index)
{
   while (index != Null)
   {
      int left = nodes[index].left;
      int right = nodes[index].right;

      nodes[index].height = 1 + 
         max(nodes[left].height, nodes[right].height);
      //nodes[index].aabb = Combine(this->at(left), this->at(right));

      index = nodes[index].parent;
   }
   
}
