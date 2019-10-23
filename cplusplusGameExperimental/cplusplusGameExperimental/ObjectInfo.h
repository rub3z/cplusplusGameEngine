#pragma once
#include <iostream>
class ObjectInfo {
   friend class AABBTree;
   friend class State;
public:
   float posX, posY;
   float width, height;
   int collisionIndex;
   int drawIndex;
   int r, g, b;
   int type;

   void** vTable;

   ObjectInfo() {
      posX = 0.0f; posY = 0.0f;
      width = 0.0f; height = 0.0f;
      collisionIndex = -1;
      drawIndex = 0;
      r = 0; g = 0; b = 0;
   }

   void hit(ObjectInfo * that) {
      ((void(*)(ObjectInfo*, ObjectInfo*))this->vTable[0])(this,that);
   };
};