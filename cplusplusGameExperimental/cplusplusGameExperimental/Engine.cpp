#include "stdafx.h"
#include "Engine.h"

Engine::Engine()
{
   // Get the screen resolution and create an SFML window and View
   sf::Vector2u resolution;
   resolution.x = RESOLUTION_X;
   resolution.y = RESOLUTION_Y;
   
   m_Window.create(sf::VideoMode(resolution.x, resolution.y),
      "MY SHOOTER GAME WOO"
      // Comment/uncomment this line to change between
      // windowed or fullscreen mode.
      , sf::Style::Fullscreen
   );

   m_Window.setPosition(sf::Vector2i(0,0));

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
   
   gameState.add(player0);
   //gameState.add(player1);
   //gameState.add(enemy0);
   //gameState.add(enemy1);
   //gameState.add(enemy2);
   gameState.add(enemies);
   gameState.add(bullets);
}

void Engine::start()
{
   // Timing
   long long int frameTime = 0;
   long long int tickRate = 16666; // 60 per second
   float tickFloat = (float)tickRate / 1000000;
   float alpha = 0;

   long long int accumulator = 0;
   
   auto previousTime = std::chrono::steady_clock::now();

   while (m_Window.isOpen())
   {
      // Restart the clock and save the elapsed time into dt
      auto dt = std::chrono::duration_cast<std::chrono::microseconds>
         (std::chrono::steady_clock::now() - previousTime);
      previousTime = std::chrono::steady_clock::now();

      // Make a fraction from the delta time (frameTime)
      frameTime = dt.count();
      if (frameTime > 25000) frameTime = 25000;

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
   std::cout << sf::VertexBuffer::isAvailable() << "\n";
   std::cout << "Number of objects in simulation: " << gameState.size() << "\n";

   // Performance Logging
   sf::Clock perfClock;
   int sumTime = 0;
   int saveSumTime = 0;
   int inputSumTime = 0;
   int updateSumTime = 0;
   int collSumTime = 0;

   int second = 0;
   int updateLoopTimes[LOG_DENSITY];
   int saveTimes[LOG_DENSITY];
   int inputTimes[LOG_DENSITY];
   int updateTimes[LOG_DENSITY];
   int collTimes[LOG_DENSITY];

   int updates = 0;

   int drawSumTime = 0;
   int drawTimes[LOG_DENSITY];
   updateLoopTimes[0] = 0;
   saveTimes[0] = 0;
   inputTimes[0] = 0;
   updateTimes[0] = 0;
   collTimes[0] = 0;

   drawTimes[0] = 0;
   int draws = 0;
   int numDraws[LOG_DENSITY];

   // Timing
   long long int frameTime = 0;
   long long int tickRate =
      //8333;  // 120 ticks per second
      //10000; // 100 per second
      16666; // 60 per second
      //0.02f; // 50 per second
      //0.0333333f; // 30 per second
   float tickFloat = (float)tickRate / 1000000;
   float alpha = 0;

   long long int accumulator = 0;
   
   auto previousTime = std::chrono::steady_clock::now();
   
   while (m_Window.isOpen())
   {
      // Restart the clock and save the elapsed time into dt
      auto dt = std::chrono::duration_cast<std::chrono::microseconds>
         (std::chrono::steady_clock::now() - previousTime);
      previousTime = std::chrono::steady_clock::now();

      // Make a fraction from the delta time (frameTime)
      frameTime = dt.count();
      if (frameTime > 25000) frameTime = 25000;
      
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
         if (second < LOG_DENSITY) {
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
         if (second == LOG_DENSITY) {
            std::cout << "Number of AABBs: " <<  aabbTree.getSize() << "\n";
            for (int i = 1; i < LOG_DENSITY; i++) {
               std::cout << "Avg Save " << i << ": "
                  << saveTimes[i] << " - ";
               std::cout << "Avg Input " << i << ": "
                  << inputTimes[i] << " - ";
               std::cout << "Avg Update " << i << ": "
                  << updateTimes[i] << "\n";
               std::cout << "Avg Coll " << i << ": "
                  << collTimes[i] << " - ";
               std::cout << "Avg Update Loop " << i << ": "
                  << updateLoopTimes[i];
               std::cout << " - Avg Draw Time " << i << ": "
                  << drawTimes[i] << " - Draws: " << numDraws[i] << "\n";
            }

            int sa = 0, ia = 0, ua = 0, ca = 0, ula = 0, da = 0, ad = 0;
            for (int i = 1; i < LOG_DENSITY; i++) {
               sa += saveTimes[i];
               ia += inputTimes[i];
               ua += updateTimes[i];
               ca += collTimes[i];
               ula += updateLoopTimes[i];
               da += drawTimes[i];
               ad += numDraws[i];
            }
            sa /= LOG_DENSITY - 1; ia /= LOG_DENSITY - 1; ua /= LOG_DENSITY - 1; 
            ca /= LOG_DENSITY - 1; ula /= LOG_DENSITY - 1; da /= LOG_DENSITY - 1; 
            ad /= LOG_DENSITY - 1;
            std::cout << "AVG SAVE 5s: " << sa << " - ";
            std::cout << "AVG INPUT 5s: " << ia << " - ";
            std::cout << "AVG UPDATE 5s: " << ua << "\n  ";
            std::cout << "AVG UPDATE LOOP 5s: " << ula << " - ";
            std::cout << "AVG DRAW 5s: " << da << " - ";
            std::cout << "AVG DRAWS 5s: " << ad << "\n\n";

            second = 0;
         }
         updates = 0;
         draws = 0;
      }
   }
}
