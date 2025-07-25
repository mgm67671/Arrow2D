#include "InputManager.hpp"

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

/**
 * @brief Checks if a specific keyboard key is currently pressed.
 *
 * This function queries the current state of the keyboard and returns true
 * if the specified SDL_Scancode key is being held down.
 *
 * @param key The SDL_Scancode representing the key to check.
 * @return true if the key is currently pressed, false otherwise.
 */
bool InputManager::IsKeyDown(SDL_Scancode key)
{
    const bool* state = SDL_GetKeyboardState(NULL);
    return state != nullptr && state[key];
}