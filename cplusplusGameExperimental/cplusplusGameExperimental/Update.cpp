#include "stdafx.h"
#include "Engine.h"

using namespace sf;

void Engine::update(float& dtAsSeconds)
{
   currentState.clear();
   player0.update(dtAsSeconds);
   currentState.add(player0.getSprite());

   for (Projectile& p : bullets) {
      p.update(dtAsSeconds);
      currentState.add(p.getSprite());
   }

   enemy.update(dtAsSeconds, player0.getPosition());
   currentState.add(enemy.getSprite());

   for (Enemy& e : enemies) {
      e.update(dtAsSeconds, player0.getPosition());
      currentState.add(e.getSprite());
   }


   //player1.update(dtAsSeconds);
   //player2.update(dtAsSeconds);
   
   /*for (Projectile& p : bullets) {
      p.update(dtAsSeconds);
      for (Enemy& e : enemies) {
         e.update(dtAsSeconds, player0.getPosition());
         if (areColliding(e.getSprite(), p.getSprite()))
            e.hit();
      }
   }*/
   //for (Projectile& p : bullets) p.update(dtAsSeconds);
   //for (Enemy& e : enemies) e.update(dtAsSeconds, player0.getPosition());
   //enemy.update(dtAsSeconds, player0.getPosition());
   //if (areColliding(enemy.getSprite(), player0.getSprite()))
     // enemy.hit();
   //for (Projectile& p : bullets) {
   //   if (areColliding(enemy.getSprite(), p.getSprite()))
   //      enemy.hit();



}