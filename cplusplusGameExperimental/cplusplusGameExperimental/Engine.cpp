#include "stdafx.h"
#include "Engine.h"

Engine::Engine()
{
   // Get the screen resolution and create an SFML window and View
   sf::Vector2u resolution;
   resolution.x = RESOLUTION_X;
   resolution.y = RESOLUTION_Y;
   fireRateDeltaPlayer0 = 0;
   fireRateDeltaPlayer1 = 0;
   fireRateDeltaPlayer2 = 0;
   fireRateDeltaPlayer3 = 0;

   m_Window.create(sf::VideoMode(resolution.x, resolution.y),
      "MY SHOOTER GAME WOO"
      // Comment/uncomment this line to change between
      // windowed or fullscreen mode.
      //, Style::Fullscreen
   );

   m_Window.setPosition(sf::Vector2i(0, 0));

   m_Window.setMouseCursorVisible(false);

   // Load the background texture.
   m_BackgroundTexture.loadFromFile("background.jpg");

   // Associate the sprite with the texture.
   m_BackgroundSprite.setTexture(m_BackgroundTexture);

   aabbTree.add(player0);
   //aabbTree.add(player1);
   //aabbTree.add(enemy0);
   //aabbTree.add(enemy1);
   //aabbTree.add(enemy2);
   //for (int i = 0; i < MAX_ENEMY1; i++) {
   //   aabbTree.add(enemies[i]);
   //}

   gameState.add(player0);
   //gameState.add(player1);
   //gameState.add(enemy0);
   //gameState.add(enemy1);
   //gameState.add(enemy2);
   gameState.add(bullets);
   gameState.add(enemies);
}

void Engine::start()
{
   // Timing
   dtAsSeconds = 0;
   frameTime = 0;
   sf::Int64 deltaTime = 0;
   sf::Int64 tickRate = 16666; // 60 updates per second
   float tickFloat = (float)tickRate / 1000000;
   float alpha = 0;
   sf::Int64 accumulator = 0;

   sf::Clock clock;
   sf::Time dt;

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
         // Save the current game state into the previous one.
         gameState.save();
         
         // Input. Have to increment fireRateDelta time.
         input(tickFloat);
         
         // Step the game state forward.
         update(tickFloat);

         aabbTree.update();
         
         accumulator -= tickRate;
      }
      
      alpha = (float)accumulator / tickRate;
      gameState.interpolate(alpha);
      draw(gameState);
   }
}

void Engine::startWithLogs()
{
   cout << sf::VertexBuffer::isAvailable() << "\n";
   cout << "Number of objects in simulation: " << gameState.size() << "\n";

   // Timing
   dtAsSeconds = 0;
   frameTime = 0;
   sf::Int64 deltaTime = 0;
   sf::Int64 tickRate =
      //8333;  // 120 ticks per second
      //10000; // 100 per second
      16666; // 60 per second
      //0.02f; // 50 per second
      //0.0333333f; // 30 per second
   float tickFloat = (float)tickRate / 1000000;
   float alpha = 0;
   sf::Int64 accumulator = 0;

   sf::Clock clock;
   sf::Time dt;

   // Performance Logging
   sf::Clock perfClock;
   int sumTime = 0;
   int saveSumTime = 0;
   int inputSumTime = 0;
   int updateSumTime = 0;
   int collSumTime = 0;

   int second = 0;
   int updateLoopTimes[11];
   int saveTimes[11];
   int inputTimes[11];
   int updateTimes[11];
   int collTimes[11];

   int updates = 0;

   int drawSumTime = 0;
   int drawTimes[11];
   updateLoopTimes[0] = 0;
   saveTimes[0] = 0;
   inputTimes[0] = 0;
   updateTimes[0] = 0;
   collTimes[0] = 0;

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
         saveSumTime += (int) perfClock.getElapsedTime().asMicroseconds();

         // Input. Have to increment fireRateDelta time.
         input(tickFloat);
         inputSumTime += (int) perfClock.getElapsedTime().asMicroseconds();

         // Step the game state forward.
         update(tickFloat);
         updateSumTime += (int) perfClock.getElapsedTime().asMicroseconds();

         aabbTree.update();
         collSumTime += (int)perfClock.getElapsedTime().asMicroseconds();

         accumulator -= tickRate;

         // PERFORMANCE CLOCK CHECK
         sumTime += (int) perfClock.getElapsedTime().asMicroseconds();
         updates++;
      }
      // PERFORMANCE CLOCK RESET
      perfClock.restart();

      alpha = (float)accumulator / tickRate;
      gameState.interpolate(alpha);
      draw(gameState);

      // PERFORMANCE CLOCK CHECK
      drawSumTime += (int) perfClock.getElapsedTime().asMicroseconds();
      draws++;

      if (updates == 60) {
         second++;
         if (second < 11) {
            collSumTime -= updateSumTime;
            updateSumTime -= inputSumTime;
            inputSumTime -= saveSumTime;
            saveTimes[second] = saveSumTime / updates;
            inputTimes[second] = inputSumTime / updates;
            updateTimes[second] = updateSumTime / updates;
            collTimes[second] = collSumTime / updates;
            updateLoopTimes[second] = sumTime / updates;
            drawTimes[second] = drawSumTime / draws;
            numDraws[second] = draws;
         }
         sumTime = 0; saveSumTime = 0; inputSumTime = 0; updateSumTime = 0;
         collSumTime = 0; drawSumTime = 0; draws = 0;
         if (second == 11) {
            cout << "Number of AABBs: " <<  aabbTree.getSize() << "\n";
            for (int i = 1; i < 11; i++) {
               cout << "Avg Save " << i << ": "
                  << saveTimes[i] << " - ";
               cout << "Avg Input " << i << ": "
                  << inputTimes[i] << " - ";
               cout << "Avg Update " << i << ": "
                  << updateTimes[i] << "\n   ";
               cout << "Avg Coll " << i << ": "
                  << collTimes[i] << " - ";
               cout << "Avg Update Loop " << i << ": "
                  << updateLoopTimes[i];
               cout << " - Avg Draw Time " << i << ": "
                  << drawTimes[i] << " - Draws: " << numDraws[i] << "\n";
            }

            int sa = 0, ia = 0, ua = 0, ca = 0, ula = 0, da = 0, ad = 0;
            for (int i = 1; i < 11; i++) {
               sa += saveTimes[i];
               ia += inputTimes[i];
               ua += updateTimes[i];
               ca += collTimes[i];
               ula += updateLoopTimes[i];
               da += drawTimes[i];
               ad += numDraws[i];
            }
            sa /= 10; ia /= 10; ua /= 10; ca /= 10; 
            ula /= 10; da /= 10; ad /= 10;
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

