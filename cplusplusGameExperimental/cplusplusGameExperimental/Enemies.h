#pragma once
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "ConstantsNStuff.h"
#include "RectangularBoundaryCollision.h"
#include "GameObject.h"


using namespace sf;
using namespace std;
using namespace collision;

class Enemies : public vector<GameObject> {
   GameObject baseSprite;
   Texture pTexture;

   int enemyType;
   float velX[MAX_ENEMY1];
   float velY[MAX_ENEMY1];
   float pAccX, pAccY;
   float distance;
   float distanceX;
   float distanceY;
   
public:
   Enemies();
   Enemies(int type);
   void collisionCheck(Sprite& other);
   void update(float & elapsedTime, float& playerPosX, float& playerPosY);
};