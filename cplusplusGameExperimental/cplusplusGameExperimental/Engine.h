// This code is modified from a gamecodeschool.com tutorial:
// http://gamecodeschool.com/sfml/building-a-simple-game-engine-in-c-plus-plus/
// Thanks to John Horton on getting me started.

#pragma once
#include "State.h"
#include "Player.h"
#include "Projectiles.h"
#include "Enemy.h"
#include "Enemies.h"
#include "AABB.h"
#include "AABBTree.h"
#include <iostream>

class Engine
{
private:

   // A regular RenderWindow.
   sf::RenderWindow m_Window;

   // Declare a sprite and a Texture for the background.
   sf::Sprite m_BackgroundSprite;
   sf::Texture m_BackgroundTexture;

   // An instance of Player.
   Player player0 = Player(0);
   Player player1 = Player(1);
   Player player2 = Player(2);
   Enemy enemy0 = Enemy(0);
   Enemy enemy1 = Enemy(1);
   Enemy enemy2 = Enemy(2);
  
   int bulletCounter;
   int spreadBulletCounter;
   float fireRateDeltaPlayer0;
   float fireRateDeltaPlayer1;
   float fireRateDeltaPlayer2;
   float fireRateDeltaPlayer3;

   Projectiles bullets;

   Enemies enemies = Enemies();

   State gameState;
   AABBTree aabbTree;

   sf::Int64 dtAsSeconds;
   sf::Int64 frameTime;

   // Private functions for internal use only.
   void input();
   void update(float& dtAsSeconds);
   void draw(State & drawState);

   // Input method to make testing new inputs and controls easier.
   void input(float& dtAsSeconds);

public:
   // The Engine constructor.
   Engine();

   // start will call all the private functions.
   void start();

   // This will execute with print outs to the console every ten seconds.
   void startWithLogs();

};