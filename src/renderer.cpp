#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, 
                   const std::size_t grid_height , 
                   Level &level)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height),
      _lvl(&level){
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  // Create a window with the specified position, dimensions, and flags.
  /*
  SDL_Window * SDL_CreateWindow(const char *title , int x , int y , int w , int h , Uint32 flags);
  */
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, screen_width,screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Snake const snake, SDL_Point const &food) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF); // black
  SDL_RenderClear(sdl_renderer);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF); //yellow
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF); //white
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }
    // Render borders //808080 silver
  SDL_SetRenderDrawColor(sdl_renderer, 0x80, 0x80, 0x80, 0xFF); //silver
  for(SDL_Point const &point : _lvl->getBorders())
  {
  block.x = point.x * block.w;
  block.y = point.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF); //blue
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF); //red
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps ) {
  std::string difficulty;
  if(_lvl->getDifficulty() == Level::Difficulty::kEasy)
  {
    difficulty = "Easy mode";
  }
  else if (_lvl->getDifficulty() == Level::Difficulty::kMedium)
  {
    difficulty = "Medium mode";
  }
  else if (_lvl->getDifficulty() == Level::Difficulty::kHard)
  {
    difficulty = "Hard mode";
  }
    else if (_lvl->getDifficulty() == Level::Difficulty::kSupersaiyan)
  {
    difficulty = "Supersaiyan mode Wow !!";
  }
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps) + " Mode : " + difficulty};
  SDL_SetWindowTitle(sdl_window, title.c_str()); //c_str returns a const char* that points to a null-terminated string (i.e. a C-style string). It is useful when you want to pass the "contents"¹ of an std::string to a function that expects to work with a C-style string.
}


