#pragma once
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
//#include "AABBTree.h"
#include "ConstantsNStuff.h"
#include "RectangularBoundaryCollision.h"


using namespace sf;
using namespace std;
using namespace collision;

class AABB : public Sprite {
   friend class AABBTree;
   bool IsLeaf(void) const
   {
      // The right leaf does not use the same memory as the userdata,
      // and will always be Null (no children)
      return right == Null;
   }

   union
   {
      int parent;
      int next; // free list
   };

   union
   {
      // Child indices
      struct
      {
         int left;
         int right;
      };
      
      // Since only leaf nodes hold userdata, we can use the
      // same memory used for left/right indices to store
      // the userdata void pointer
      void *userData;
   };

   // leaf = 0, free nodes = -1
   int height;
   static const int Null = -1;


public:
   void update();
};
