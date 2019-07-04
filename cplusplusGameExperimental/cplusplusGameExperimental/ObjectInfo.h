#pragma once
class ObjectInfo {
   friend class State;
public:
   float posX, posY;
   float width, height;
   int collisionIndex;
   int drawIndex;
   int r, g, b;

   ObjectInfo() {
      posX = 0.0f; posY = 0.0f;
      width = 0.0f; height = 0.0f;
      collisionIndex = -1;
      drawIndex = 0;
      r = 0; g = 0; b = 0;
   }
};