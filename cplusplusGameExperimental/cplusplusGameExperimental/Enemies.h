#pragma once
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <vector>


using namespace sf;
using namespace std;

class Enemies : public vector<Sprite> {
   Sprite baseSprite;
   Texture pTexture;

   int enemyType;
   float pVelX, pVelY;
   float pAccX, pAccY;
   float distance;
   float distanceX;
   float distanceY;
   
public:
   Enemies();
   Enemies(int type);
   void hit(FloatRect& other);
   void hit();
   void update(float & elapsedTime, const Vector2f& playerPos);
};