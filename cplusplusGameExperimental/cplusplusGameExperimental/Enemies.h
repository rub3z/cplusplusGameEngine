// Adapted from code used in this tutorial:
// https://www.sfml-dev.org/tutorials/2.5/graphics-vertex-array.php
#pragma once
#include "stdafx.h"
#include <vector>
#include <execution>
#include "GameObject.h"

struct EnemyInfo {
   int index;
   float distanceX, distanceY;
   float pAccX, pAccY;
   float distance;
   bool flag;
};

class Enemies : public std::vector<GameObject> {
public:
   Enemies::Enemies();
   void update(float& elapsedTime, float& posX, float& posY);
   void doit();
   std::vector<GameObject*> flagged;

private:
   std::vector<EnemyInfo> info;

   void * vT[3];
};