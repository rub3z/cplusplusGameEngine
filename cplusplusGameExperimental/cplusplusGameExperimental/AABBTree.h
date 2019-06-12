#pragma once
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "AABB.h"
#include "Enemy.h"
#include "ConstantsNStuff.h"
#include "RectangularBoundaryCollision.h"

using namespace sf;
using namespace std;
using namespace collision;

static const int Null = -1;

class AABBTree : public vector<AABB> {
   int x;
   int y;
public:
   AABBTree();
   void syncHierarchy(int index);

};