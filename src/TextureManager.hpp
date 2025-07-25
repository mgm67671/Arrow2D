#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include <SDL3/SDL.h>
#include <unordered_map>
#include <string>
#include "GameObject.hpp"

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
        /**
         * @brief Gets the singleton instance of the TextureManager.
         */
        static TextureManager& Instance();

        /**
         * @brief Loads a texture from the specified file path using the given SDL renderer.
         *        Caches textures for reuse.
         * @param path The file system path to the image file to load.
         * @param renderer The SDL_Renderer to use for creating the texture.
         * @return A pointer to the loaded SDL_Texture, or nullptr if loading fails.
         */
        SDL_Texture *LoadTexture(const std::string &path, SDL_Renderer *renderer);

        /**
         * @brief Releases all loaded textures and cleans up resources managed by the TextureManager.
         */
        void Clean();

    private:
        TextureManager() = default;
        TextureManager(const TextureManager&) = delete;
        TextureManager& operator=(const TextureManager&) = delete;
        std::unordered_map<std::string, SDL_Texture *> textureCache;
};

#endif // TEXTUREMANAGER_HPP
