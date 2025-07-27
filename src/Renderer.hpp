#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SDL3/SDL.h>
#include "GameObject.hpp"


/**
 * @class Renderer
 * @brief Singleton class responsible for managing all 2D rendering operations using SDL.
 *
 * The Renderer class encapsulates the SDL_Renderer and provides a set of methods to initialize,
 * clear, render game objects, and present the rendered content to the screen. It follows the singleton
 * pattern to ensure only one renderer instance exists throughout the application's lifetime.
 *
 * Usage:
 *   - Call Renderer::Instance() to access the singleton instance.
 *   - Use Init() to initialize the renderer with an SDL_Window.
 *   - Use Clean(), Render(), and Present() for the main rendering loop.
 *   - Retrieve the underlying SDL_Renderer pointer with GetSDLRenderer() if needed.
 */
class Renderer
{
    public:
        /// @brief Returns the singleton instance of the Renderer.
        /// @return Reference to the single Renderer instance.
        static Renderer& Instance();

        /**
         * @brief Clears the current rendering target using the renderer.
         *
         * This function clears the entire rendering target to the preset draw color,
         * preparing it for new drawing operations.
         *
         * @note This function uses the global or member variable `sdlRenderer` as the SDL renderer.
         * @see SDL_RenderClear
         */
        void Clean();

        /**
         * @brief Renders the specified game object.
         *
         * This function handles the rendering logic for the provided GameObject instance.
         *
         * @param obj Reference to the GameObject to be rendered.
         */
        void Render(GameObject &obj);

        /**
         * @brief Presents the current rendering on the screen.
         *
         * This function updates the window with any rendering performed since the previous call.
         * It wraps SDL_RenderPresent to display the rendered content using the associated SDL renderer.
         */
        void Present();

        /**
         * @brief Retrieves the underlying SDL_Renderer pointer.
         *
         * @return A pointer to the SDL_Renderer used for rendering operations.
         */
        SDL_Renderer *GetSDLRenderer() const;

        /**
         * @brief Initializes the SDL renderer for the game window.
         *
         * This method creates the SDL_Renderer using the provided SDL_Window pointer.
         * It must be called before any rendering or texture loading occurs.
         *
         * @param window The SDL_Window to associate with the renderer.
         * @return true if the renderer was created successfully, false otherwise.
         */
        bool Init(SDL_Window *window);

    private:
        /**
         * @brief Default constructor for the Renderer class.
         *
         * Initializes a Renderer object with default settings.
         */
        Renderer() = default;

        /// Pointer to the SDL_Renderer used for rendering graphics to the window.
        /// This renderer is responsible for all 2D drawing operations in the application.
        SDL_Renderer *sdlRenderer;
};

#endif // RENDERER_HPP
