
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "GameObject.hpp"
#include "InputManager.hpp"
#include <unordered_map>
#include <string>
#include <SDL3/SDL.h>

/**
 * @class Player
 * @brief Represents the player character in the game, handling movement, input, and animation.
 *
 * The Player class inherits from GameObject and encapsulates logic for player-specific behavior,
 * including movement, input handling, and animation state management. It utilizes a TextureManager
 * for loading and managing textures, and interacts with an InputManager for processing user input.
 *
 * Key Features:
 * - Construction with initial position, animation textures, speed, and rendering context.
 * - Per-frame update logic for movement and state.
 * - Input handling for responsive player control.
 * - Animation state updates based on movement and facing direction.
 * - Getters and setters for movement speed.
 *
 * @see GameObject
 * @see TextureManager
 * @see InputManager
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
         * @brief Virtual destructor for safe polymorphic deletion.
         */
        virtual ~Player() = default;

        
        /**
         * @brief Updates the player's state.
         * 
         * This method is called every frame to update the player's logic,
         * such as movement, input handling, and interactions.
         * 
         * @param dt The time elapsed since the last update (delta time), in seconds.
         */
        void Update(float dt) override;

        
        /**
         * @brief Handles player input and updates player state accordingly.
         * 
         * Processes input events using the provided InputManager and updates the player's
         * state based on the elapsed time since the last update.
         * 
         * @param input Reference to the InputManager handling user input.
         * @param dt Delta time in seconds since the last frame.
         */
        void HandleInput(InputManager& input, float dt);

        
        /**
         * @brief Updates the player's animation state.
         *
         * This function updates the animation based on the elapsed time, movement state,
         * and the direction the player is facing.
         *
         * @param dt The time elapsed since the last update (in seconds).
         * @param moving Indicates whether the player is currently moving.
         * @param facingRight Indicates whether the player is facing to the right.
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
        float speed; // Movement speed in pixels per second.
};

#endif // PLAYER_HPP
