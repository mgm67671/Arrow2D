#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include <SDL3/SDL.h>
#include <unordered_map>
#include <string>
#include "GameObject.hpp"

/**
 * @class TextureManager
 * @brief Manages loading, caching, and cleanup of SDL textures in a singleton pattern.
 *
 * The TextureManager class provides a centralized interface for loading textures from files,
 * caching them for efficient reuse, and releasing resources when they are no longer needed.
 * It ensures that each texture is loaded only once and reused throughout the application,
 * minimizing redundant resource usage. The class is implemented as a singleton to guarantee
 * a single point of management for all texture resources.
 *
 * Usage:
 *   - Use TextureManager::Instance() to access the singleton instance.
 *   - Call LoadTexture() to load and retrieve textures.
 *   - Call Clean() to release all loaded textures and free associated resources.
 */
class TextureManager 
{
    public:
        /**
         * @brief Provides access to the singleton instance of the TextureManager.
         * @return TextureManager& Reference to the singleton TextureManager instance.
         */
        static TextureManager& Instance();

        /**
         * @brief Loads a texture from the specified file path using the given SDL renderer.
         *
         * This function attempts to load an image file and create an SDL_Texture that can be used for rendering.
         *
         * @param path The file system path to the image file to load.
         * @param renderer The SDL_Renderer to use for creating the texture.
         * @return A pointer to the loaded SDL_Texture, or nullptr if loading fails.
         */
        SDL_Texture *LoadTexture(const std::string &path, SDL_Renderer *renderer);

        /**
         * @brief Releases all loaded textures and cleans up resources managed by the TextureManager.
         *
         * This function should be called to free memory and resources associated with textures
         * before shutting down the application or when textures are no longer needed.
         */
        void Clean();

    private:
        /**
         * @brief Default constructor for the TextureManager class.
         *
         * Initializes a new instance of the TextureManager.
         * This constructor does not perform any specific initialization logic.
         */
        TextureManager() = default;
        std::unordered_map<std::string, SDL_Texture *> textureCache; 
};

#endif // TEXTUREMANAGER_HPP
