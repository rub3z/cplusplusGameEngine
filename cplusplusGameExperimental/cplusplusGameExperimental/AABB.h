#pragma once
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include "ConstantsNStuff.h"
#include "ObjectInfo.h"
#include "RectangularBoundaryCollision.h"


using namespace sf;
using namespace std;

class AABB : public RectangleShape {
   friend class AABBTree;

   float centerX;
   float centerY;
   float radiusX;
   float radiusY;

   ObjectInfo* obj;
   
public:
   AABB() : centerX(), centerY(), radiusX(), radiusY() {}

   AABB(const float& cX, const float& cY,
      const float& rX, const float& rY)
      : centerX(cX), centerY(cY)
      , radiusX(rX), radiusY(rY)
   {}
   AABB(ObjectInfo & objVertex);
   void update();
};
