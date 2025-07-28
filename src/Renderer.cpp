#include "Renderer.hpp"
#include <SDL3/SDL.h>
#include <iostream>

Renderer& Renderer::Instance() 
{
    static Renderer instance;
    return instance;
}

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

void Renderer::Clean()
{
    SDL_RenderClear(sdlRenderer);
}

void Renderer::Render(GameObject &obj, float offsetX, float offsetY)
{
    // Render the GameObject using the SDL renderer, applying camera offset
    SDL_FRect dest = obj.GetDestRect();
    dest.x -= offsetX;
    dest.y -= offsetY;
    SDL_RenderTexture(sdlRenderer, obj.GetTexture(), NULL, &dest);
}

void Renderer::Present()
{
    SDL_RenderPresent(sdlRenderer);
}

SDL_Renderer *Renderer::GetSDLRenderer() const
{
    return sdlRenderer;
}