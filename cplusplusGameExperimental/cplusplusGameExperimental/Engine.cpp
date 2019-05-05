#include "stdafx.h"
#include "Engine.h"

Engine::Engine()
{
   // Get the screen resolution and create an SFML window and View
   Vector2f resolution;
   resolution.x = 1920;
   resolution.y = 1080;
   bulletCounter = 0;
   spreadBulletCounter = 0;
   fireRateDeltaPlayer0 = 0;
   fireRateDeltaPlayer1 = 0;
   fireRateDeltaPlayer2 = 0;
   fireRateDeltaPlayer3 = 0;


   m_Window.create(VideoMode(resolution.x, resolution.y),
      "MY SHOOTER GAME WOO"
      // Comment/uncomment this line to change between
      // windowed or fullscreen mode.
      , Style::Fullscreen
   );

   m_Window.setMouseCursorVisible(false);

   // Load the background texture.
   m_BackgroundTexture.loadFromFile("background.jpg");

   // Associate the sprite with the texture.
   m_BackgroundSprite.setTexture(m_BackgroundTexture);
   
   gameState.add(&player0);

   for (Projectile & p : bullets) {
      gameState.add(&p);
   }
   
   enemies = Enemies(2);
   for (int i = 0; i < MAX_ENEMY1; i++) {
      gameState.add(&enemies[i]);
   }

}

void Engine::start()
{
   // Timing
   dtAsSeconds = 0;
   frameTime = 0;
   Int64 deltaTime = 0;
   Int64 tickRate =
      //8333;  // 120 ticks per second
      //10000; // 100 per second
      16666; // 60 per second
      //0.02f; // 50 per second
      //0.0333333f; // 30 per second
   float tickFloat = (float)tickRate / 1000000;
   float alpha = 0;
   Int64 accumulator = 0;
   
   Clock clock;
   Time dt;

   
   while (m_Window.isOpen())
   {
      // Restart the clock and save the elapsed time into dt
      dt = clock.getElapsedTime();

      // Make a fraction from the delta time (frameTime)
      frameTime = dt.asMicroseconds() - dtAsSeconds;
      //if (frameTime > 250000) frameTime = 250000;
      dtAsSeconds = dt.asMicroseconds();

      accumulator += frameTime;

      while (accumulator >= tickRate) {

         gameState.save();
         fireRateDeltaPlayer0 += tickFloat;
         input();
         update(tickFloat);
         
         accumulator -= tickRate;
      }
      alpha = (float)accumulator / tickRate;

      gameState.interpolate(alpha);

      draw(gameState);      
   }
}

