#pragma once
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "RectangularBoundaryCollision.h"


using namespace sf;
using namespace std;
using namespace collision;

class Enemies : public vector<Sprite> {
   Sprite baseSprite;
   Texture pTexture;

   int enemyType;
   vector<Vector2f> vel;
   float pVelX, pVelY;
   float pAccX, pAccY;
   float distance;
   float distanceX;
   float distanceY;
   
public:
   Enemies();
   Enemies(int type);
   void collisionCheck(Sprite& other);
   void update(float & elapsedTime, const Vector2f& playerPos);
};