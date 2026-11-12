#include "DisplayServer.h"

#include <SDL.h>

#include <cmath>
#include <chrono>
#include <iostream>
#include <thread>

int main() {
   if (SDL_Init(SDL_INIT_VIDEO) != 0) {
      std::cerr << "SDL initialization failed: " << SDL_GetError() << '\n';
      return 1;
   }

   SDL_Window* window = SDL_CreateWindow(
      "Analog Display",
      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      500, 500, SDL_WINDOW_SHOWN);
   SDL_Renderer* renderer = window
      ? SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)
      : nullptr;

   if (!window || !renderer) {
      std::cerr << "Could not create analog display window: "
                << SDL_GetError() << '\n';
      if (renderer) SDL_DestroyRenderer(renderer);
      if (window) SDL_DestroyWindow(window);
      SDL_Quit();
      return 1;
   }

   unsigned int value = 0;
   DisplayServer server(4712, [&value](unsigned int newValue) {
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
      SDL_SetRenderDrawColor(renderer, 18, 18, 22, 255);
      SDL_RenderClear(renderer);

      constexpr int centerX = 250;
      constexpr int centerY = 270;
      constexpr int radius = 180;
      for (int angle = 135; angle <= 405; angle += 2) {
         const double radians = angle * 3.141592653589793 / 180.0;
         const int x1 = centerX + static_cast<int>(radius * std::cos(radians));
         const int y1 = centerY + static_cast<int>(radius * std::sin(radians));
         const int x2 = centerX + static_cast<int>((radius - 12) * std::cos(radians));
         const int y2 = centerY + static_cast<int>((radius - 12) * std::sin(radians));
         SDL_SetRenderDrawColor(renderer, 180, 180, 190, 255);
         SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
      }

      const double fraction = (value % 221) / 220.0;
      const double needleAngle = (135.0 + 270.0 * fraction) *
                                 3.141592653589793 / 180.0;
      const int needleX = centerX + static_cast<int>((radius - 25) *
                                                     std::cos(needleAngle));
      const int needleY = centerY + static_cast<int>((radius - 25) *
                                                     std::sin(needleAngle));
      SDL_SetRenderDrawColor(renderer, 230, 60, 60, 255);
      SDL_RenderDrawLine(renderer, centerX, centerY, needleX, needleY);

      SDL_RenderPresent(renderer);
      std::this_thread::sleep_for(std::chrono::milliseconds(16));
   }

   SDL_DestroyRenderer(renderer);
   SDL_DestroyWindow(window);
   SDL_Quit();
   return 0;
}
