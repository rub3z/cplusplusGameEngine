#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "GameObject.h"


using namespace sf;
using namespace std;

class EnemiesOld : public vector<GameObject> {
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
   EnemiesOld();
   EnemiesOld(int type);
   void collisionCheck(Sprite& other);
   void update(float & elapsedTime, float& playerPosX, float& playerPosY);
};