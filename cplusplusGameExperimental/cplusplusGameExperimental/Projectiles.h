#pragma once
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "ConstantsNStuff.h"
#include "RectangularBoundaryCollision.h"


using namespace sf;
using namespace std;
using namespace collision;

class Projectiles : public vector<Sprite> {
   Sprite baseSprite;
   Texture pTexture;

   int pIterator;
   float moveX[MAX_BULLETS];
   float moveY[MAX_BULLETS];
   float lifeTimeCounter[MAX_BULLETS];
   

public:
   Projectiles();
   void shootStraight(const Vector2f& pos, float& vX, float& vY);
   void shootSpread(const Vector2f& pos, float& vX, float& vY);
   void collisionCheck(Sprite& other);
   void update(float & elapsedTime);
};