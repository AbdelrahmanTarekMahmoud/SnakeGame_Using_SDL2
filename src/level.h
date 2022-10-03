#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "SDL.h"

class Level
{
public:
   enum class  Difficulty {kEasy , kMedium , kHard , kSupersaiyan};
   Difficulty difficulty = Difficulty::kEasy;
   
   Level();
   
   void setDifficulty();
   Difficulty getDifficulty();

   void readBorders();
   std::vector<SDL_Point> getBorders();

   bool BorderCell(int &x, int &y);

private:
    std::vector<SDL_Point>Borders{};
};
#endif