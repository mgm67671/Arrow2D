#include "Renderer.hpp"
#include <SDL3/SDL.h>
#include <iostream>

Renderer& Renderer::Instance() 
{
    static Renderer instance;
    return instance;
}

/**
 * @brief Initializes the SDL renderer for the game window.
 *
 * This method creates the SDL_Renderer using the provided SDL_Window pointer.
 * It must be called before any rendering or texture loading occurs.
 *
 * @param window The SDL_Window to associate with the renderer.
 * @return true if the renderer was created successfully, false otherwise.
 */
bool Renderer::Init(SDL_Window *window)
{
    if (sdlRenderer)
    {
        SDL_DestroyRenderer(sdlRenderer);
        sdlRenderer = nullptr;
    }
    
    sdlRenderer = SDL_CreateRenderer(window, NULL);
    if (!sdlRenderer)
    {
        std::cerr << "Failed to create SDL_Renderer: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

/// @brief Clears the current rendering target using the renderer.
/// 
/// This function clears the entire rendering target to the preset draw color,
/// preparing it for new drawing operations.
/// 
/// @note This function uses the global or member variable `sdlRenderer` as the SDL renderer.
/// 
/// @see SDL_RenderClear
void Renderer::Clean()
{
    SDL_RenderClear(sdlRenderer);
}

/**
 * @brief Renders the specified game object.
 * 
 * This function handles the rendering logic for the provided GameObject instance.
 * 
 * @param obj Reference to the GameObject to be rendered.
 */
void Renderer::Render(GameObject &obj)
{
    // Render the GameObject using the SDL renderer
    SDL_RenderTexture(sdlRenderer, obj.GetTexture(), NULL, &obj.GetDestRect());
}

/**
 * @brief Presents the current rendering on the screen.
 *
 * This function updates the window with any rendering performed since the previous call.
 * It wraps SDL_RenderPresent to display the rendered content using the associated SDL renderer.
 */
void Renderer::Present()
{
    SDL_RenderPresent(sdlRenderer);
}

/**
 * @brief Retrieves the underlying SDL_Renderer pointer.
 * 
 * @return A pointer to the SDL_Renderer used for rendering operations.
 */
SDL_Renderer *Renderer::GetSDLRenderer() const
{
    return sdlRenderer;
}