#include "stdafx.h"
#include "AABB.h"

AABB::AABB(const float& lX, const float& lY, const float& uX, const float& uY)
{
   lowerBoundX = lX; lowerBoundY = lY; upperBoundX = uX; upperBoundY = uY;
   objectPtr = NULL;
   //setDrawBounds();
}

AABB::AABB(GameObject & obj) {
   objectPtr = &obj;
   lowerBoundX = objectPtr->posX - AABB_FATNESS;
   lowerBoundY = objectPtr->posY - AABB_FATNESS;
   upperBoundX = objectPtr->posX + objectPtr->width  + AABB_FATNESS;
   upperBoundY = objectPtr->posY + objectPtr->height + AABB_FATNESS;
   //setDrawBounds();
}
