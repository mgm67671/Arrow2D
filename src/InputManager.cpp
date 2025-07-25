#include "InputManager.hpp"
#include "GameConfig.hpp"

InputManager& InputManager::Instance() 
{
    static InputManager instance;
    return instance;
}

/// @brief Updates the input manager state each frame.
/// Call this function once per frame to process input events and update internal states.
void InputManager::Update()
{
    ProcessInput();
}

/// @brief Processes input events from the SDL event queue.
/// This function should be called in the main loop to handle user input.
void InputManager::ProcessInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
            Engine::Instance().SetRunning(false);
    }
}

bool InputManager::IsKeyDown(SDL_Scancode key)
{
    const bool* state = SDL_GetKeyboardState(NULL);
    bool pressed = state != nullptr && state[key];
    return pressed;
}

void InputManager::GetMovementVector(float& vx, float& vy, float speed)
{
    vx = 0.0f;
    vy = 0.0f;
    if (IsKeyDown(KEY_MOVE_UP)    || IsKeyDown(KEY_UP_ALT))    vy -= 1.0f;
    if (IsKeyDown(KEY_MOVE_DOWN)  || IsKeyDown(KEY_DOWN_ALT))  vy += 1.0f;
    if (IsKeyDown(KEY_MOVE_LEFT)  || IsKeyDown(KEY_LEFT_ALT))  vx -= 1.0f;
    if (IsKeyDown(KEY_MOVE_RIGHT) || IsKeyDown(KEY_RIGHT_ALT)) vx += 1.0f;
    // Normalize
    float len = sqrtf(vx * vx + vy * vy);
    if (len > 0.0f) 
    {
        vx = (vx / len) * speed;
        vy = (vy / len) * speed;
    }
}