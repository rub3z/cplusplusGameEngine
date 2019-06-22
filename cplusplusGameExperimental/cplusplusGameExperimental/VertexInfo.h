#pragma once
class VertexInfo {
   friend class State;
public:
   float posX, posY;
   int r, g, b;

   VertexInfo() {
      posX = 0.0f;
      posY = 0.0f;
      r = 0;
      g = 0;
      b = 0;
   }

};