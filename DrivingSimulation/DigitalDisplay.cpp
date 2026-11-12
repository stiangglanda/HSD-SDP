#include "DisplayServer.h"

#include <SDL.h>

#include <chrono>
#include <iostream>
#include <thread>

static void DrawDigit(SDL_Renderer* renderer, int digit, int x, int y, int size) {
   static constexpr bool segments[10][7] = {
      {true, true, true, true, true, true, false},
      {false, true, true, false, false, false, false},
      {true, true, false, true, true, false, true},
      {true, true, true, true, false, false, true},
      {false, true, true, false, false, true, true},
      {true, false, true, true, false, true, true},
      {true, false, true, true, true, true, true},
      {true, true, true, false, false, false, false},
      {true, true, true, true, true, true, true},
      {true, true, true, true, false, true, true}
   };
   const int thickness = size / 5;
   const int length = size;
   const SDL_Rect segmentRects[7] = {
      {x + thickness, y, length, thickness},
      {x + length, y + thickness, thickness, length},
      {x + length, y + length + thickness, thickness, length},
      {x + thickness, y + 2 * length, length, thickness},
      {x, y + length + thickness, thickness, length},
      {x, y + thickness, thickness, length},
      {x + thickness, y + length, length, thickness}
   };

   SDL_SetRenderDrawColor(renderer, 40, 210, 120, 255);
   for (int segment = 0; segment < 7; ++segment) {
      if (segments[digit][segment]) {
         SDL_RenderFillRect(renderer, &segmentRects[segment]);
      }
   }
}

int main() {
   if (SDL_Init(SDL_INIT_VIDEO) != 0) {
      std::cerr << "SDL initialization failed: " << SDL_GetError() << '\n';
      return 1;
   }

   SDL_Window* window = SDL_CreateWindow(
      "Digital Display",
      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      640, 240, SDL_WINDOW_SHOWN);
   SDL_Renderer* renderer = window
      ? SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)
      : nullptr;

   if (!window || !renderer) {
      std::cerr << "Could not create digital display window: "
                << SDL_GetError() << '\n';
      if (renderer) SDL_DestroyRenderer(renderer);
      if (window) SDL_DestroyWindow(window);
      SDL_Quit();
      return 1;
   }

   unsigned int value = 0;
   DisplayServer server(4711, [&value](unsigned int newValue) {
      value = newValue;
   });
   server.Start();

   bool running = true;
   while (running) {
      SDL_Event event;
      while (SDL_PollEvent(&event)) {
         if (event.type == SDL_QUIT) {
            running = false;
         }
      }

      server.Poll();
      SDL_SetRenderDrawColor(renderer, 20, 20, 24, 255);
      SDL_RenderClear(renderer);

      SDL_Rect panel{20, 20, 600, 200};
      SDL_SetRenderDrawColor(renderer, 35, 35, 45, 255);
      SDL_RenderFillRect(renderer, &panel);

      const unsigned int displayedValue = value % 1000;
      DrawDigit(renderer, displayedValue / 100, 145, 55, 45);
      DrawDigit(renderer, (displayedValue / 10) % 10, 265, 55, 45);
      DrawDigit(renderer, displayedValue % 10, 385, 55, 45);

      SDL_RenderPresent(renderer);
      std::this_thread::sleep_for(std::chrono::milliseconds(16));
   }

   SDL_DestroyRenderer(renderer);
   SDL_DestroyWindow(window);
   SDL_Quit();
   return 0;
}
