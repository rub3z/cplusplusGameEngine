#pragma once
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "GameObject.h"


using namespace std;
using namespace sf;

class State : public Drawable {
private:
   friend class State;
   vector<GameObject> previous;
   vector<GameObject *> current;
   virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

   int keepSize;

public:
   void clear();
   void interpolate(float alphaNum);
   //void interpolateI(float alphaNum, int begin, int end);
   void add(GameObject * s);
   void save();
   int size();
};