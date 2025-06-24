#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include <SDL3/SDL.h>
#include <unordered_map>
#include <string>

/**
 * @class TextureManager
 * @brief Manages loading and caching of textures for efficient reuse.
 *
 * The TextureManager class provides functionality to load textures from files,
 * cache them to avoid redundant loading, and clean up resources when no longer needed.
 */
class TextureManager 
{
    public:
        static TextureManager& Instance();
        SDL_Texture *LoadTexture(const std::string &path, SDL_Renderer *renderer);
        void Clean();
    private:
        TextureManager() = default;
        TextureManager(const TextureManager&) = delete;
        TextureManager& operator=(const TextureManager&) = delete;
        std::unordered_map<std::string, SDL_Texture *> textureCache;
};

#endif // TEXTUREMANAGER_HPP
