#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <cassert>
#include "Enemy.h"
#include "AABB.h"

using namespace std;

static const int Null = -1;
static const AABB NULL_AABB = AABB(1, 1, 1, 1);
 
class AABBTree : public sf::Drawable {
   struct Node {
      bool IsLeaf(void) const
      {
         return right == Null;
      };

      int parent;
      
      // Child indices
      int left;
      int right;
      
      int next; // free list
      //void* userData;
      
      // leaf = 0, free nodes = -1
      int height;
      
      AABB aabb;

      Node() {
         this->aabb = NULL_AABB;
         parent = Null;
         next = Null;
         left = Null;
         right = Null;
         height = 0;
      }

      Node(int id) {
         this->aabb = NULL_AABB;
         parent = Null;
         next = id;
         left = Null;
         right = Null;
         height = 0;
      }

      Node(AABB& newAABB) {
         this->aabb = newAABB;
         parent = Null;
         next = Null;
         left = Null;
         right = Null;
         height = 0;
      };
   };

   int root;
   int free;
   int numNodes;
   int maxNodes;
   std::vector<Node> nodes;
   std::vector<GameObject*> addStack;
   std::vector<int> removeStack;
   std::vector<int> leaves;

   virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

   int allocNode();
   void freeNode(int index);

   void insertLeaf(GameObject& objInfo);
   void removeLeaf(int index);
   void syncHierarchy(int index);
   int balance(int index);
   bool testOverLap(AABB& a, AABB& b);
   AABB combine(AABB& a, AABB& b);

   struct Collision {
      int idA; int idB;

      Collision(int idX, int idY) {
         idA = idX; idB = idY;
      }
   };

   int numPairs;
   int maxPairs;
   std::vector<Collision> pairs;

   inline void GrowFreeList(int index);

   //template <typename T>
   //inline 
   void Query(AABB& aabb); //const;

   void GetCollisionPairs();
   bool TreeCallBack(int idA, int idB);
   void resolveCollisions();

public:
   AABBTree();
   void add(GameObject& objInfo);
   void remove(int index);
   void update();
   int getSize();
   int getCapacity();
};

// Adapted from code used here:
// https://www.randygaul.net/2013/08/06/dynamic-aabb-tree/
inline void AABBTree::GrowFreeList(int index)
{
   maxNodes *= 2;
   nodes.resize(maxNodes);
   for (int i = index; i < maxNodes - 1; ++i)
   {
      nodes[i].next = i + 1;
      nodes[i].height = Null;
   }

   nodes[maxNodes - 1].next = Null;
   nodes[maxNodes - 1].height = Null;
   free = index;
}

// Adapted from code used here:
// https://www.randygaul.net/2013/08/06/dynamic-aabb-tree/
//template<typename T>
//inline 
inline void AABBTree::Query(AABB& aabb)// const
{
   const int stackCapacity = 256;
   int stack[stackCapacity];
   int sp = 1;

   *stack = root;

   while (sp) {
      assert(sp < stackCapacity); // stack capacity too small!
      int id = stack[--sp];

      Node* n = nodes.data() + id;
      if (testOverLap(aabb, n->aabb)) {
         if (n->IsLeaf()) {
            // Report, via callback, a collision with leaf
            if (!TreeCallBack(aabb.objectPtr->collisionIndex, id))
               return;
         }
         else {
            stack[sp++] = n->left;
            stack[sp++] = n->right;
         }
      }
   }
}