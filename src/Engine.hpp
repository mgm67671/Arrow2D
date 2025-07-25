#ifndef ENGINE_HPP
#define ENGINE_HPP

// Forward declarations for subsystems
class Renderer;
class InputManager;
class TextureManager;

#include "GameObject.hpp"
#include "Scene.hpp"


/**
 * @class Engine
 * @brief Singleton class responsible for managing the core game loop and subsystems.
 *
 * The Engine class encapsulates the main functionality required to initialize,
 * run, and clean up the game. It manages subsystems such as rendering, input,
 * and texture management, and provides a singleton interface to ensure only one
 * instance exists throughout the application's lifetime.
 */
class Engine
{
    public:
        /// @brief Returns the singleton instance of the Engine.
        /// @return Reference to the single Engine instance.
        static Engine& Instance();

        /**
         * @brief Initializes the engine with the specified window title and dimensions.
         *
         * This function sets the window title, width, and height for the engine,
         * and marks the engine as running.
         *
         * @param title The title of the window.
         * @param width The width of the window in pixels.
         * @param height The height of the window in pixels.
         * @return true if initialization was successful, false otherwise.
         */
        bool Init(const char *title, int width, int height);

        /**
         * @brief Releases resources and cleans up dynamically allocated objects.
         *
         * This function deletes the scene object to free up memory and prevent resource leaks.
         * It should be called during the shutdown or cleanup phase of the application.
         */
        void Clean();

        /**
         * @brief Main loop of the engine.
         *
         * Continuously runs while the engine is active. In each iteration,
         * it handles input events, updates the game state, and renders the scene.
         * The loop exits when the 'running' flag is set to false.
         */
        void Run();

        /**
         * @brief Handles input events and updates the input manager state.
         *
         * This function processes all pending SDL events, such as keyboard and mouse input,
         * and updates the input manager's state accordingly. It also checks for quit events
         * to allow the engine to exit gracefully.
         */
        void HandleEvents();

        /**
         * @brief Updates the game state based on input and elapsed time.
         *
         * This function processes input from the user, updates the scene,
         * and handles movement logic.
         *
         * @param dt The time delta since the last update in seconds.
         */
        void Update(double dt);

        /**
         * @brief Renders the current scene using the renderer.
         *
         * This function clears the renderer, renders all game objects in the scene,
         * and presents the rendered frame to the screen.
         */
        void Render();

        /**
         * @brief Sets the running state of the engine.
         * 
         * This function updates the internal state to indicate whether the engine
         * should be running or stopped.
         * 
         * @param state True to set the engine as running, false to stop it.
         */
        void SetRunning(bool state);

    private:
        /// @brief Default constructor for the Engine class.
        Engine() = default;

        /// @brief Destructor for the Engine class.
        ~Engine() = default;

        const char *title;
        int width;
        int height;
        bool running;
        Renderer *renderer;
        InputManager *inputManager;
        TextureManager *textureManager;
        GameObject *player;
        Scene *scene;
};

#endif // ENGINE_HPP
