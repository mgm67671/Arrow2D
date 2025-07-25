#include "TextureManager.hpp"

TextureManager& TextureManager::Instance() 
{
    static TextureManager instance;
    return instance;
}

SDL_Texture *TextureManager::LoadTexture(const std::string &path, SDL_Renderer *renderer)
{
    // Check if the texture is already cached
    auto it = textureCache.find(path);
    if (it != textureCache.end())
        return it->second;

    // Load the texture from file
    SDL_Surface *surface = SDL_LoadBMP(path.c_str());
    if (!surface)
    {
        SDL_Log("Failed to load BMP: %s", SDL_GetError());
        return nullptr;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    if (!texture)
    {
        SDL_Log("Failed to create texture: %s", SDL_GetError());
        return nullptr;
    }

    // Cache the texture
    textureCache[path] = texture;
    return texture;
}

void TextureManager::Clean()
{
    for (auto &pair : textureCache)
        SDL_DestroyTexture(pair.second);
    textureCache.clear();
}

