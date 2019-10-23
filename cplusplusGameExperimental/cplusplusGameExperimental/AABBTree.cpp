#include "stdafx.h"
#include "AABBTree.h"

void AABBTree::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   for (Node n : nodes) {
      target.draw(n.aabb);
   }
}

AABBTree::AABBTree()
{ 
   root = Null;
   numNodes = 0;
   maxNodes = 4;
   GrowFreeList(0);
}

void AABBTree::add(ObjectInfo& objInfo) {
   addStack.push_back(&objInfo);
}

void AABBTree::remove(int index) {
   removeStack.push_back(index);
}

int AABBTree::allocNode() {
   int index = free;
   nodes[index].parent = Null;
   nodes[index].left = Null;
   nodes[index].right = Null;
   nodes[index].height = 0;
   free = nodes[index].next;
   numNodes++;
   if (numNodes == maxNodes) GrowFreeList(numNodes);
   return index;
}

void AABBTree::freeNode(int index) {
   nodes[index].parent = Null;
   nodes[index].next = free;
   nodes[index].left = Null;
   nodes[index].right = Null;
   nodes[index].height = Null;
   nodes[index].aabb = NULL_AABB;
   free = index;
   numNodes--;
}

// This code is modified code from Erin Catto's Box2D code, line 176
// of /Collision/b2DynamicTree.cpp as of 7/9/2019:
// https://github.com/erincatto/Box2D/blob/master/Box2D/Collision/b2DynamicTree.cpp
void AABBTree::insertLeaf(ObjectInfo& objInfo) {
   if (root == Null) {
      root = allocNode();
      nodes[root].aabb = AABB(objInfo);
      objInfo.collisionIndex = root;
      leaves.push_back(root);
      return;
   }
   
   int leaf = allocNode();
   nodes[leaf].aabb = AABB(objInfo);
   objInfo.collisionIndex = leaf;
   leaves.push_back(leaf);
   
   AABB newAABB = nodes[leaf].aabb;
   int index = root;
   while (nodes[index].IsLeaf() == false) {
      int leftChildIndex = nodes[index].left;
      int rightChildIndex = nodes[index].right;

      float area = nodes[index].aabb.getPerimeter();

      AABB combined = combine(nodes[index].aabb, newAABB);
      float combinedArea = combined.getPerimeter();

      // Cost of creating a new parent for this node and the new leaf
      float cost = 2.0f * combinedArea;

      // Minimum cost of pushing the leaf further down the tree
      float inheritanceCost = 2.0f * (combinedArea - area);

      //Cost of descending to leftChildIndex
      float costLeft;
      if (nodes[leftChildIndex].IsLeaf()) {
         AABB childAABB = combine(newAABB, nodes[leftChildIndex].aabb);
         costLeft = childAABB.getPerimeter() + inheritanceCost;
      }
      else {
         AABB childAABB = combine(newAABB, nodes[leftChildIndex].aabb);
         float oldArea = nodes[leftChildIndex].aabb.getPerimeter();
         float newArea = childAABB.getPerimeter();
         costLeft = (newArea - oldArea) + inheritanceCost;
      }

      //Cost of descending to rightChildIndex
      float costRight;
      if (nodes[rightChildIndex].IsLeaf()) {
         AABB childAABB = combine(newAABB, nodes[rightChildIndex].aabb);
         costRight = childAABB.getPerimeter() + inheritanceCost;
      }
      else {
         AABB childAABB = combine(newAABB, nodes[rightChildIndex].aabb);
         float oldArea = nodes[rightChildIndex].aabb.getPerimeter();
         float newArea = childAABB.getPerimeter();
         costRight = (newArea - oldArea) + inheritanceCost;
      }

      // Descend according to the minimum cost.
      if (cost < costLeft && cost < costRight) break;

      //Descend (choose index of next node to check against).
      index = costLeft < costRight ?
         leftChildIndex : rightChildIndex;
   }

   int sibling = index;
   int oldParent = nodes[sibling].parent;
   
   int newParent = allocNode();
   
   nodes[newParent].aabb = combine(newAABB, nodes[sibling].aabb);
   nodes[newParent].parent = oldParent;
   nodes[newParent].height = nodes[sibling].height + 1;
   nodes[newParent].left = sibling;
   nodes[newParent].right = leaf;
   nodes[sibling].parent = newParent;
   nodes[leaf].parent = newParent;

   if (oldParent != Null) {
      // The sibling was not the root.
      if (nodes[oldParent].left == sibling) {
         nodes[oldParent].left = newParent;
      }
      else {
         nodes[oldParent].right = newParent;
      }
   }
   else {
      // The sibling was the root.
      root = newParent;
   }

   // Walk back up the tree fixing heights and AABBs.
   index = nodes[leaf].parent;
   syncHierarchy(index);
}

void AABBTree::removeLeaf(int index) {
   if (index == root) {
      root = Null;
      return;
   }

   int parent = nodes[index].parent;
   int grandpa = nodes[parent].parent;
   int sibling = nodes[parent].left == index ?
      nodes[parent].right : nodes[parent].left;

   // There is a grandparent, remove parent and replace it with the sibling.
   if (grandpa != Null) {
      if (nodes[grandpa].left == parent) {
         nodes[grandpa].left = sibling;
      }
      else {
         nodes[grandpa].right = sibling;
      }

      nodes[sibling].parent = grandpa;

      freeNode(parent);

      syncHierarchy(grandpa);
   }
   else { // The parent is the root.
      root = sibling;
      nodes[sibling].parent = Null;

      freeNode(parent);
   }
   nodes[index].parent = Null;
}

bool AABBTree::testOverLap(AABB& a, AABB& b)
{
   if (fabs(a.centerX - b.centerX) > (a.radiusX + b.radiusX)) return false;
   if (fabs(a.centerY - b.centerY) > (a.radiusY + b.radiusY)) return false;
   return true;
}

void AABBTree::update() {
   for (int i = 0; i < addStack.size(); i++) {
      insertLeaf(*addStack[i]);
   }
   
   for (int i = 0; i < removeStack.size(); i++) {
      assert(nodes[removeStack[i]].IsLeaf());
      removeLeaf(removeStack[i]);
      freeNode(removeStack[i]);
   }

   addStack.clear();
   removeStack.clear();

   for (int i = 0; i < nodes.size(); i++) {
      if (nodes[i].aabb.objectPtr) {
         if (nodes[i].aabb.objectCollisionRemoved()) {
             remove(i);
             leaves.erase(
                std::remove(leaves.begin(), leaves.end(), i), leaves.end());
         }
         else {
            nodes[i].aabb.update();
         }
      }
      else {
         int left = nodes[i].left;
         int right = nodes[i].right;
         if (nodes[i].height >= 0) {
            nodes[i].aabb = combine(nodes[left].aabb, nodes[right].aabb);
         }
      }
   }

   GetCollisionPairs();
   resolveCollisions();
}

void AABBTree::GetCollisionPairs() {
   pairs.clear();
   for (int i : leaves) {
      Query(nodes[i].aabb);
   }
}

bool AABBTree::TreeCallBack(int idA, int idB) {
   if (idA == idB) return true;
   pairs.emplace_back(idA, idB);
   return true;
}

void AABBTree::resolveCollisions() {
   if (pairs.size() > 0) {
      for (Collision c : pairs) {
         nodes[c.idA].aabb.objectPtr->hit(nodes[c.idB].aabb.objectPtr);
      }
   }
}

inline AABB AABBTree::combine(AABB& a, AABB& b) {
   float upperBoundx = max(a.centerX + a.radiusX, b.centerX + b.radiusX);
   float upperBoundy = max(a.centerY + a.radiusY, b.centerY + b.radiusY);
   float lowerBoundx = min(a.centerX - a.radiusX, b.centerX - b.radiusX);
   float lowerBoundy = min(a.centerY - a.radiusY, b.centerY - b.radiusY);

   float abCenterX = (upperBoundx + lowerBoundx) / 2;
   float abCenterY = (upperBoundy + lowerBoundy) / 2;
   float abRadiusX = upperBoundx - abCenterX;
   float abRadiusY = upperBoundy - abCenterY;

   return AABB(abCenterX, abCenterY, abRadiusX, abRadiusY);
}

int AABBTree::getSize() {
   return numNodes;
}

int AABBTree::getCapacity() {
   return maxNodes;
}

void AABBTree::syncHierarchy(int index)
{
   while (index != Null)
   {
      index = balance(index);

      int left = nodes[index].left;
      int right = nodes[index].right;

      assert(left != Null);
      assert(right != Null);

      nodes[index].height = 1 +
         max(nodes[left].height, nodes[right].height);
      nodes[index].aabb = combine(nodes[left].aabb, nodes[right].aabb);

      index = nodes[index].parent;
   }
}

int AABBTree::balance(int index) {
   assert(index != Null);

   if (nodes[index].IsLeaf() || nodes[index].height < 2) return index;

   int leftChild = nodes[index].left;
   int rightChild = nodes[index].right;

   assert(0 <= leftChild && leftChild < maxNodes);
   assert(0 <= rightChild && rightChild < maxNodes);

   int balance = nodes[rightChild].height - nodes[leftChild].height;

   // Right child is imbalanced, rotate it up.
   if (balance > 1) {
      int rleftGChild = nodes[rightChild].left;
      int rrightGChild = nodes[rightChild].right;

      assert(0 <= rleftGChild && rleftGChild < maxNodes);
      assert(0 <= rrightGChild && rrightGChild < maxNodes);

      nodes[rightChild].left = index;
      nodes[rightChild].parent = nodes[index].parent;
      nodes[index].parent = rightChild;

      //node's old parent should point to right child.
      int rightParent = nodes[rightChild].parent;
      if (rightParent != Null) {
         if (nodes[rightParent].left == index) {
            nodes[rightParent].left = rightChild;
         }
         else {
            //assert(nodes[rightParent].right == index);
            nodes[rightParent].right = rightChild;
         }
      }
      else {
         root = rightChild;
      }

      // Rotate
      if (nodes[rleftGChild].height > nodes[rrightGChild].height) {
         nodes[rightChild].right = rleftGChild;
         nodes[index].right = rrightGChild;
         nodes[rrightGChild].parent = index;

         //nodes[index].aabb = combine(nodes[leftChild].aabb, nodes[rrightGChild].aabb);
         //nodes[rightChild].aabb = combine(nodes[index].aabb, nodes[rleftGChild].aabb);

         nodes[index].height = 1 + max(nodes[leftChild].height, nodes[rrightGChild].height);
         nodes[rightChild].height = 1 + max(nodes[index].height, nodes[rleftGChild].height);
      }
      else {
         nodes[rightChild].right = rrightGChild;
         nodes[index].right = rleftGChild;
         nodes[rleftGChild].parent = index;

         //nodes[index].aabb = combine(nodes[leftChild].aabb, nodes[rleftGChild].aabb);
         //nodes[rightChild].aabb = combine(nodes[index].aabb, nodes[rrightGChild].aabb);

         nodes[index].height = 1 + max(nodes[leftChild].height, nodes[rleftGChild].height);
         nodes[rightChild].height = 1 + max(nodes[index].height, nodes[rrightGChild].height);
      }

      return rightChild;
   }

   // Rotate the left child up.
   if (balance < -1) {
      int lleftGChild = nodes[leftChild].left;
      int lrightGChild = nodes[leftChild].right;

      assert(0 <= lleftGChild && lleftGChild < maxNodes);
      assert(0 <= lrightGChild && lrightGChild < maxNodes);

      nodes[leftChild].left = index;
      nodes[leftChild].parent = nodes[index].parent;
      nodes[index].parent = leftChild;

      // old parent should point to left child
      int leftParent = nodes[leftChild].parent;
      if (leftParent != Null) {
         if (nodes[leftParent].left == index) {
            nodes[leftParent].left = leftChild;
         }
         else {
            //assert(nodes[leftParent].right == index);
            nodes[leftParent].right = leftChild;
         }
      }
      else {
         root = leftChild;
      }

      // Rotate
      if (nodes[lleftGChild].height > nodes[lrightGChild].height) {
         nodes[leftChild].right = lleftGChild;
         nodes[index].left = lrightGChild;
         nodes[lrightGChild].parent = index;

         //nodes[index].aabb = combine(nodes[rightChild].aabb, nodes[lrightGChild].aabb);
         //nodes[leftChild].aabb = combine(nodes[index].aabb, nodes[lleftGChild].aabb);

         nodes[index].height = 1 + max(nodes[rightChild].height, nodes[lrightGChild].height);
         nodes[leftChild].height = 1 + max(nodes[index].height, nodes[lleftGChild].height);
      }
      else {
         nodes[leftChild].right = lrightGChild;
         nodes[index].left = lleftGChild;
         nodes[lleftGChild].parent = index;

         //nodes[index].aabb = combine(nodes[rightChild].aabb, nodes[lleftGChild].aabb);
         //nodes[leftChild].aabb = combine(nodes[index].aabb, nodes[lrightGChild].aabb);

         nodes[index].height = 1 + max(nodes[rightChild].height, nodes[lleftGChild].height);
         nodes[leftChild].height = 1 + max(nodes[index].height, nodes[lrightGChild].height);
      }

      return leftChild;
   }

   return index;
}

