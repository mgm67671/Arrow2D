#include "TextureManager.hpp"

TextureManager& TextureManager::Instance() 
{
    static TextureManager instance;
    return instance;
}

/**
 * @brief Loads a texture from the specified file path using the given SDL renderer.
 *
 * This function attempts to load an image file and create an SDL_Texture that can be used for rendering.
 *
 * @param path The file system path to the image file to load.
 * @param renderer The SDL_Renderer to use for creating the texture.
 * @return A pointer to the loaded SDL_Texture, or nullptr if loading fails.
 */
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

/**
 * @brief Releases all loaded textures and cleans up resources managed by the TextureManager.
 *
 * This function should be called to free memory and resources associated with textures
 * before shutting down the application or when textures are no longer needed.
 */
void TextureManager::Clean()
{
    for (auto &pair : textureCache)
        SDL_DestroyTexture(pair.second);
    textureCache.clear();
}