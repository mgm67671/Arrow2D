#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include <SDL3/SDL.h>
#include "Engine.hpp"


/**
 * @class InputManager
 * @brief Singleton class responsible for handling input events and state.
 *
 * The InputManager class manages keyboard input for the application. It provides
 * methods to update input state, process SDL events, query key states, and calculate
 * movement vectors based on user input. Designed as a singleton to ensure a single
 * point of input management throughout the application.
 *
 * Usage:
 *   - Call InputManager::Instance() to access the singleton instance.
 *   - Call Update() once per frame to refresh input states.
 *   - Use ProcessInput() to handle SDL input events.
 *   - Use IsKeyDown() to check if a specific key is pressed.
 *   - Use GetMovementVector() to obtain normalized movement vectors based on input.
 */
class InputManager
{
    public:
        /**
         * @brief Gets the singleton instance of the InputManager.
         */
        static InputManager& Instance();

        /**
         * @brief Updates the input manager state each frame.
         */
        void Update();

        /**
         * @brief Processes input events from the SDL event queue.
         */
        void ProcessInput();

        /**
         * @brief Checks if a specific keyboard key is currently pressed.
         *
         * This function queries the current state of the keyboard and returns true
         * if the specified SDL_Scancode key is being held down.
         *
         * @param key The SDL_Scancode representing the key to check.
         * @return true if the key is currently pressed, false otherwise.
         */
        bool IsKeyDown(SDL_Scancode key);

        /**
         * @brief Gets the movement vector based on current input and speed.
         *
         * This function calculates the movement vector based on the current input state,
         * normalizes it, and scales it by the specified speed. It updates the provided
         * vx and vy parameters with the calculated values.
         *
         * @param vx Reference to store the calculated X velocity.
         * @param vy Reference to store the calculated Y velocity.
         * @param speed The speed to scale the movement vector.
         */
        void GetMovementVector(float& vx, float& vy, float speed);

    private:
        /// @brief Default constructor for the InputManager class.
        ///        Initializes a new instance of InputManager with default settings.
        InputManager() = default;
};

#endif // INPUTMANAGER_HPP
