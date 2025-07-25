
#pragma once
#include "GameObject.hpp"
#include "InputManager.hpp"
#include <unordered_map>
#include <string>
#include <SDL3/SDL.h>

/**
 * @class Player
 * @brief Represents the player character, handling input, movement, and animation.
 *
 * The Player class extends GameObject to provide player-specific logic, including
 * input handling, movement, and animation state updates. It is designed to be modular
 * and only handles logic relevant to the player-controlled character.
 */
class Player : public GameObject 
{
    public:

        /**
         * @brief Constructs a Player object at the specified position, loads its textures, and sets speed.
         * @param x Initial x-coordinate.
         * @param y Initial y-coordinate.
         * @param texturePaths Map of animation states to texture file paths.
         * @param speed Movement speed in pixels per second.
         * @param textureManager Pointer to the TextureManager.
         * @param renderer SDL_Renderer to use for loading textures.
         */
        Player(float x, float y, const std::unordered_map<AnimState, std::string>& texturePaths, float speed, TextureManager* textureManager, SDL_Renderer* renderer);


        /**
         * @brief Updates the player each frame (handles input, movement, and animation).
         * @param dt Time delta since last update (in seconds).
         */
        void Update(float dt) override;

        /**
         * @brief Handles input and updates velocity and animation state.
         * @param inputManager Reference to the InputManager.
         * @param dt Time delta since last update (in seconds).
         */
        void HandleInput(InputManager& inputManager, float dt);

        /**
         * @brief Updates the animation state based on movement and direction.
         * @param dt Time delta since last update (in seconds).
         * @param moving Whether the player is moving.
         * @param facingRight Whether the player is facing right.
         */
        void UpdateAnim(float dt, bool moving, bool facingRight) override;

        /**
         * @brief Sets the player's movement speed.
         * @param speed New speed value.
         */
        void SetSpeed(float speed);

        /**
         * @brief Gets the player's movement speed.
         * @return Current speed value.
         */
        float GetSpeed() const;
    private:
        float speed; ///< Movement speed in pixels per second.
};
