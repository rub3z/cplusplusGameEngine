#pragma once
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
//#include "AABB.h"
#include "Enemy.h"
#include "ConstantsNStuff.h"
#include "RectangularBoundaryCollision.h"

using namespace sf;
using namespace std;
using namespace collision;

static const int Null = -1;

class AABBTree {//: public vector<Node> {

   struct AABB {
      friend class AABBTree;

      AABB() : centerX(), centerY(), radiusX(), radiusY() {}

      AABB(const float& cX, const float& cY,
         const float& rX, const float& rY)
         : centerX(cX), centerY(cY)
         , radiusX(rX), radiusY(rY)
      {}

      float centerX;
      float centerY;
      float radiusX;
      float radiusY;
   };

   struct Node {
      bool IsLeaf(void) const
      {
         // The right leaf does not use the same memory as the userdata,
         // and will always be Null (no children)
         return right == Null;
      }

      AABB aabb;

      int parent;
      int next; // free list
      

      // Child indices
      int left;
      int right;
      
      void* userData;
      
      // leaf = 0, free nodes = -1
      int height;
      static const int Null = -1;
   };

   vector<Node> nodes;

public:
   AABBTree();
   void syncHierarchy(int index);

};