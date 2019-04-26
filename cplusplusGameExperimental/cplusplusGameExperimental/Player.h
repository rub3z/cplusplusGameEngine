#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Player {
   Vector2f pPosition;

   Sprite pSprite;

   Texture pTexture;

   // Boolean statements to check for 2D input.
   bool moveLeft, moveRight, moveUp, moveDown;

   // Alternative input control variables.
   // For possibility of joystick movement.
   float pMoveX, pMoveY;
   // or even a vector velocity variable if you're feeling fancy and want
   // to make your code more arcane and less readable.
   Vector2f pVelocity;

   float speed;

public:
   Player();
   Sprite getSprite(); // I like Sprite. Caffeine-free.
   
   void moveX(float val);

   void moveY(float val);

   void update(float elapsedTime);
};