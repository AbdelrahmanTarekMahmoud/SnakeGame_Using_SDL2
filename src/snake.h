/*
These files define the Snake class which contains attributes to keep track of the Snake speed, size, and location. 
Additionally, there are methods to update the snake state, which are called from the Game::Update method. 
The Snake head and body are treated separately; the head is stored using float coordinates,
 and the body is stored using a vector of int cell coordinates. The Snake::UpdateHead method updates the head location using the snake's speed. 
 If the head has passed into a new cell, then the body is updated with the Snake::UpdateBody.
 */
#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"
#include "level.h"

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height , Level &lvl)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2),
        _lvl(&lvl) {}

  void Update();

  void GrowBody();
  bool SnakeCell(int &x, int &y);

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  bool growing{false};
  int grid_width;
  int grid_height;

  Level *_lvl;
};

#endif