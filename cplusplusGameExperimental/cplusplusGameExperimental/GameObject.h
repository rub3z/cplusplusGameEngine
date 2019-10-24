#pragma once
#include <iostream>
class GameObject {
   friend class AABBTree;
   friend class State;
   int drawIndex;

public:
   float posX, posY;
   float width, height;
   int collisionIndex;
   int r, g, b;
   int type;
   bool flag;

   void** vTable;

   GameObject() {
      posX = 0.0f; posY = 0.0f;
      width = 0.0f; height = 0.0f;
      collisionIndex = -1;
      drawIndex = 0;
      r = 0; g = 0; b = 0;
      type = -1;
      flag = false;
   }

   void hit(GameObject * that) {
      ((void(*)(GameObject*, GameObject*))this->vTable[0])(this,that);
   };
};