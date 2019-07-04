#include "stdafx.h"
#include "Engine.h"

Engine::Engine()
{
   // Get the screen resolution and create an SFML window and View
   Vector2u resolution;
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

   //playerAABB = AABB(player0);

   gameState.add(player0);
   gameState.add(bullets);
   gameState.add(enemies);
}

void Engine::start()
{
   cout << VertexBuffer::isAvailable() << "\n";
   cout << "Number of objects in simulation: " << gameState.size() << "\n";
   
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

   // Performance Logging
   Clock perfClock;
   int sumTime = 0;
   int saveSumTime = 0;
   int inputSumTime = 0;
   int updateSumTime = 0;

   int second = 0;
   int updateLoopTimes[11];
   int saveTimes[11];
   int inputTimes[11];
   int updateTimes[11];

   int updates = 0;

   int drawSumTime = 0;
   int drawTimes[11];
   updateLoopTimes[0] = 0;
   saveTimes[0] = 0;
   inputTimes[0] = 0;
   updateTimes[0] = 0;

   drawTimes[0] = 0;
   int draws = 0;
   int numDraws[11];
   
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
         // PERFORMANCE CLOCK RESET
         perfClock.restart();

         // Save the current game state into the previous one.
         gameState.save();
         saveSumTime += perfClock.getElapsedTime().asMicroseconds();

         // Input. Have to increment fireRateDelta time.
         input(tickFloat);
         inputSumTime += perfClock.getElapsedTime().asMicroseconds();

         // Step the game state forward.
         update(tickFloat);
         updateSumTime += perfClock.getElapsedTime().asMicroseconds();

         accumulator -= tickRate;

         // PERFORMANCE CLOCK CHECK
         sumTime += perfClock.getElapsedTime().asMicroseconds();
         updates++;
      }
      // PERFORMANCE CLOCK RESET
      perfClock.restart();

      alpha = (float)accumulator / tickRate;
      gameState.interpolate(alpha);
      draw(gameState);      

      // PERFORMANCE CLOCK CHECK
      drawSumTime += perfClock.getElapsedTime().asMicroseconds();
      draws++;

      if (updates == 60) {
         second++;
         if (second < 11) {
            updateSumTime -= inputSumTime;
            inputSumTime -= saveSumTime;
            saveTimes[second] = saveSumTime / updates;
            inputTimes[second] = inputSumTime / updates;
            updateTimes[second] = updateSumTime / updates;
            updateLoopTimes[second] = sumTime / updates;
            drawTimes[second] = drawSumTime / draws;
            numDraws[second] = draws;
         }
         sumTime = 0; saveSumTime = 0; inputSumTime = 0; updateSumTime = 0;
         drawSumTime = 0; draws = 0;
         if (second == 11) {
            //cout << bulletAABBs.size() << "\n";
            for (int i = 1; i < 11; i++) {
               cout << "Avg Save " << i << ": "
                  << saveTimes[i] << " - ";
               cout << "Avg Input " << i << ": "
                  << inputTimes[i] << " - ";
               cout << "Avg Update " << i << ": "
                  << updateTimes[i] << "\n   ";
               cout << "Avg Update Loop " << i << ": "
                  << updateLoopTimes[i];
               cout << " - Avg Draw Time " << i << ": "
                  << drawTimes[i] << " - Draws: " << numDraws[i] << "\n";
            }

            int sa = 0, ia = 0, ua = 0, ula = 0, da = 0, ad = 0;
            for (int i = 1; i < 11; i++) {
               sa += saveTimes[i];
               ia += inputTimes[i];
               ua += updateTimes[i];
               ula += updateLoopTimes[i]; 
               da += drawTimes[i];
               ad += numDraws[i];
            }
            sa /= 10; ia /= 10; ua /= 10; ula /= 10; da /= 10; ad /= 10;
            cout << "AVG SAVE 10s: " << sa << " - ";
            cout << "AVG INPUT 10s: " << ia << " - ";
            cout << "AVG UPDATE 10s: " << ua << "\n  ";
            cout << "AVG UPDATE LOOP 10s: " << ula << " - ";
            cout << "AVG DRAW 10s: " << da << " - ";
            cout << "AVG DRAWS 10s: " << ad << "\n\n";

            second = 0;
         }
         updates = 0;
         draws = 0;
      }
   }
}

