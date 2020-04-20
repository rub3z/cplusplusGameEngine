#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <execution>
#include "GameObject.h"

class State : public sf::Drawable {
private:
   friend class State;

   struct DrawObject {
      int drawIndex;
      GameObject obj;
      DrawObject(int i, GameObject o) {
         drawIndex = i;
         obj = o;
      }
   };

   std::vector<sf::Vertex> toDraw;
   std::vector<DrawObject> previous;
   std::vector<GameObject * > current;
   virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
   void clear();
   void interpolate(float alphaNum);
   void add(GameObject & o);
   void add(std::vector<GameObject> & vecInfo);
   void save();
   int size();
};