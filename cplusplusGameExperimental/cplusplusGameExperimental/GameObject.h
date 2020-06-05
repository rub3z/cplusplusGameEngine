#pragma once
#include <iostream>
class GameObject {
   friend class AABBTree;
   friend class State;
   
public:
   float posX, posY;
   float width, height;
   bool collideable;
   int r, g, b;
   int type;
   
   //Data data;
   void** vTable;

   GameObject() {
      posX = 0.0f; posY = 0.0f;
      width = 0.0f; height = 0.0f;
      collideable = false;
      r = 0; g = 0; b = 0;
      type = -1;
   }

   //Data* operator->() {
   //   return &data;
   //}
};

struct Data {

};