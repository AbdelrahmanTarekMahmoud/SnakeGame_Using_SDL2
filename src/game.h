/*
These files define the Game class and the game loop: Game::Run. The Game class stores the state of the game,
 including an instance of a Snake object, the game score, and the location of "food" in the game. 
 Aside from the game loop, the Game class also contains methods to update the state of the game (Game::Update), 
 get the size of the snake, get the total score in the game, and place new food in the game if the food has been eaten by the snake.
*/
#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "level.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height , Level &lvl);
  void Run(Controller const &controller, Renderer &renderer,std::size_t target_frame_duration);

  int GetScore() const;
  int GetSize() const;

 private:
  Level *_lvl;
  Snake snake;
  SDL_Point food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceFood();
  void Update();
};

#endif