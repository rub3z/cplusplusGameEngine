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

class Projectiles : public vector<GameObject> {
   GameObject baseSprite;
   Texture pTexture;

   int pIterator;
   float moveX[MAX_BULLETS];
   float moveY[MAX_BULLETS];
   float lifeTimeCounter[MAX_BULLETS];
   

public:
   Projectiles();
   void shootStraight(float& posX, float& posY, float& vX, float& vY);
   void shootSpread(float& posX, float& posY, float& vX, float& vY);
   void collisionCheck(Sprite& other);
   void update(float & elapsedTime);
};