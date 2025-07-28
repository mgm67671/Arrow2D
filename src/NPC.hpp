#pragma once
#include "GameObject.hpp"
#include <string>
#include <map>
#include "TextureManager.hpp"

/**
 * @class NPC
 * @brief Represents a non-player character (enemy or neutral) in the game.
 *
 * Inherits from GameObject and adds any NPC-specific logic or properties.
 */
class NPC : public GameObject {
public:
    /**
     * @brief Constructs an NPC object.
     * @param x Initial X position.
     * @param y Initial Y position.
     * @param width Width of the NPC.
     * @param height Height of the NPC.
     * @param textures Map of animation states to texture file paths.
     * @param speed Movement speed.
     * @param textureManager Pointer to the TextureManager for loading textures.
     * @param sdlRenderer SDL_Renderer pointer for rendering.
     */
    NPC(float x, float y, float width, float height, const std::unordered_map<AnimState, std::string>& textures, float speed, TextureManager* textureManager, SDL_Renderer* sdlRenderer);

    /**
     * @brief Updates the NPC's logic each frame.
     * @param deltaTime Time elapsed since last frame.
     */
    void Update(float deltaTime) override;

    // Add more NPC-specific methods here if needed
};
