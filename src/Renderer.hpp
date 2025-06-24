#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SDL3/SDL.h>
#include "GameObject.hpp"

/**
 * @class Renderer
 * @brief Handles rendering operations using SDL.
 *
 * The Renderer class encapsulates an SDL_Renderer and provides methods
 * to clean the rendering target, render game objects, and present the
 * rendered frame to the screen.
 */
class Renderer
{
    public:
        static Renderer& Instance();
        void Clean();
        void Render(GameObject &obj);
        void Present();
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
        Renderer() = default;
        Renderer(const Renderer&) = delete;
        Renderer& operator=(const Renderer&) = delete;
        SDL_Renderer *sdlRenderer;
};

#endif // RENDERER_HPP
