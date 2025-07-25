#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include <SDL3/SDL.h>
#include "Engine.hpp"

/**
 * @class InputManager
 * @brief Manages and processes user input for the application.
 *
 * The InputManager class provides methods to update input states,
 * process input events, and query the state of specific keys.
 */
class InputManager
{
    public:
        static InputManager& Instance();
        void Update();
        void ProcessInput();
        bool IsKeyDown(SDL_Scancode key);
        void GetMovementVector(float& vx, float& vy, float speed);
    private:
        InputManager() = default;
        InputManager(const InputManager&) = delete;
        InputManager& operator=(const InputManager&) = delete;
};

#endif // INPUTMANAGER_HPP
