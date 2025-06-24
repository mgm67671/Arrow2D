#ifndef ENGINE_HPP
#define ENGINE_HPP

// Forward declarations for subsystems
class Renderer;
class InputManager;
class TextureManager;

#include "GameObject.hpp"

/**
 * @class Engine
 * @brief Singleton class responsible for managing the core game loop and subsystems.
 *
 * The Engine class encapsulates the main functionality required to initialize,
 * run, and clean up the game. It manages subsystems such as rendering, input,
 * and texture management, and provides a singleton interface to ensure only one
 * instance exists throughout the application's lifetime.
 *
 * @note Copy and move operations are deleted to enforce singleton behavior.
 */
class Engine
{
    public:
        static Engine& Instance(); // Singleton accessor

        // Delete copy/move constructors and assignment operators
        Engine(const Engine&) = delete;
        Engine& operator=(const Engine&) = delete;
        Engine(Engine&&) = delete;
        Engine& operator=(Engine&&) = delete;

        bool Init(const char *title, int width, int height);
        void Clean();
        void Run();
        void HandleEvents();
        void Update();
        void Render();

        //Setters
        void SetRunning(bool state);

    private:
        Engine() = default; // Private constructor
        ~Engine() = default;

        const char *title;
        int width;
        int height;
        bool running;
        Renderer *renderer;
        InputManager *inputManager;
        TextureManager *textureManager;
        GameObject *player;
};

#endif // ENGINE_HPP
