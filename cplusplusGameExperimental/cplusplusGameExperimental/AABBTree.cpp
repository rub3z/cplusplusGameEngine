#include "stdafx.h"
#include "AABBTree.h"

AABBTree::AABBTree()
{
}

void AABBTree::syncHierarchy(int index)
{
   while (index != Null)
   {
      int left = this->at(index).left;
      int right = this->at(index).right;

      this->at(index).height = 1 + 
         max(this->at(left).height, this->at(right).height);
      //this->at(index) = Combine(this->at(left), this->at(right));

      index = this->at(index).parent;
   }
   
}
