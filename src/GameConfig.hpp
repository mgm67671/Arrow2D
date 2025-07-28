#ifndef GAME_CONFIG_HPP
#define GAME_CONFIG_HPP

#include <SDL3/SDL.h>

// Window settings
constexpr const char* WINDOW_TITLE = "Arrow2D";
constexpr int WINDOW_WIDTH = 960;
constexpr int WINDOW_HEIGHT = 540;
constexpr int FPS_LIMIT = 240;

// Player settings
constexpr float PLAYER_SPEED = 300.0f; // Speed in pixels per second
constexpr float PLAYER_HOR_SIZE = 64.0f; // Horizontal size of the player sprite
constexpr float PLAYER_VER_SIZE = PLAYER_HOR_SIZE; // Vertical size of the player sprite

// Key mapping for movement (customizable)
constexpr SDL_Scancode KEY_MOVE_UP    = SDL_SCANCODE_W;
constexpr SDL_Scancode KEY_MOVE_DOWN  = SDL_SCANCODE_S;
constexpr SDL_Scancode KEY_MOVE_LEFT  = SDL_SCANCODE_A;
constexpr SDL_Scancode KEY_MOVE_RIGHT = SDL_SCANCODE_D;
constexpr SDL_Scancode KEY_UP_ALT     = SDL_SCANCODE_UP;
constexpr SDL_Scancode KEY_DOWN_ALT   = SDL_SCANCODE_DOWN;
constexpr SDL_Scancode KEY_LEFT_ALT   = SDL_SCANCODE_LEFT;
constexpr SDL_Scancode KEY_RIGHT_ALT  = SDL_SCANCODE_RIGHT;

#endif // GAME_CONFIG_HPP