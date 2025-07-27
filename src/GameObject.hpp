#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP


#include <SDL3/SDL.h>
#include <unordered_map>
#include <string>

/**
 * @enum AnimState
 * @brief Represents animation states for any game object.
 */
enum class AnimState { IdleLeft, IdleRight, WalkLeftA, WalkLeftB, WalkRightA, WalkRightB };



/**
 * @class GameObject
 * @brief Represents a basic game object with position, velocity, and animation state.
 *
 * The GameObject class provides a foundation for all objects in the game world that have a position,
 * velocity, and can be rendered with different animation states. It manages the object's position,
 * velocity, and animation state, and provides methods for updating, rendering, and controlling these properties.
 *
 * Key Features:
 * - Stores and manages the object's position (x, y) and velocity (vx, vy).
 * - Associates animation states with SDL_Texture pointers for rendering.
 * - Provides methods to update the object's state each frame, including animation state transitions.
 * - Supports setting and retrieving position, velocity, and animation state.
 * - Handles animation timing and switching between idle and walking states based on movement and direction.
 *
 * Usage:
 * - Derive from GameObject to implement specific game entities.
 * - Override Update and UpdateAnim methods to provide custom behavior.
 *
 * @note This class assumes the existence of AnimState enum and SDL2 types.
 */
class GameObject
{
    public:
        /**
         * @brief Constructs a GameObject at the specified position with associated textures for animation states.
         * 
         * @param x The x-coordinate of the GameObject's position.
         * @param y The y-coordinate of the GameObject's position.
         * @param textures A map associating each AnimState with its corresponding SDL_Texture pointer.
         */
        GameObject(float x, float y, const std::unordered_map<AnimState, SDL_Texture*>& textures);

        /**
         * @brief Updates the game object each frame.
         * @param dt Time delta since last update (in seconds).
         */
        virtual void Update(float dt);
       
        /**
         * @brief Renders the game object using the specified SDL renderer.
         * 
         * @param renderer Pointer to the SDL_Renderer used for drawing the object.
         */
        void Render(SDL_Renderer *renderer);

        /**
         * @brief Returns the texture for the current animation state, or nullptr if not found.
         * @return SDL_Texture* for the current animation state.
         */
        SDL_Texture *GetTexture() const;

        /**
         * @brief Returns the destination rectangle for rendering.
         * @return SDL_FRect representing the object's position and size.
         */
        SDL_FRect GetDestRect() const;

        /**
         * @brief Sets the object's X position.
         * @param x The new X position value to set.
         */
        void SetX(float x);
        /**
         * @brief Sets the object's Y position.
         * @param y The new Y position value to set.
         */
        void SetY(float y);

        /**
         * @brief Gets the object's X position.
         */
        float GetX() const;

        /**
         * @brief Gets the object's Y position.
         */
        float GetY() const;

        /**
         * @brief Sets the velocity of the object along the X-axis.
         * 
         * @param vx The new velocity value to set for the X-axis.
         */
        void SetVX(float vx);

        /**
         * @brief Sets the vertical velocity (VY) of the game object.
         * 
         * @param vy The new vertical velocity value to set.
         */
        void SetVY(float vy);

        /**
         * @brief Gets the object's X velocity.
         */
        float GetVX() const;

        /**
         * @brief Gets the object's Y velocity.
         */
        float GetVY() const;

        /**
         * @brief Sets the animation state of the game object.
         * 
         * This function updates the current animation state to the specified value.
         * 
         * @param state The new animation state to set for the game object.
         */
        void SetAnimState(AnimState state);

        /**
         * @brief Gets the object's animation state.
         */
        AnimState GetAnimState() const;
        
        /**
         * @brief Updates the animation state of the GameObject based on movement and direction.
         *
         * This function manages the animation timer and switches between idle and walking animation states
         * depending on whether the object is moving and which direction it is facing. It toggles between
         * animation frames at a fixed interval when moving, and resets the animation state and timer when
         * the movement state or facing direction changes.
         *
         * @param dt Time elapsed since the last update (in seconds).
         * @param moving Indicates whether the GameObject is currently moving.
         * @param facingRight Indicates whether the GameObject is facing right (true) or left (false).
         */
        virtual void UpdateAnim(float dt, bool moving, bool facingRight);

    protected:
        /// @brief Maps animation states to their corresponding SDL textures.
        /// 
        /// This unordered_map associates each AnimState (representing a specific animation state)
        /// with a pointer to an SDL_Texture, allowing efficient retrieval of the correct texture
        /// for rendering based on the current animation state.
        std::unordered_map<AnimState, SDL_Texture*> textures;

        /// @brief Represents the current animation state of the game object.
        /// Used to control and track which animation is active for this object.
        AnimState animState;

    private:
        float x, y;
        float vx, vy;
        float dt; // Delta time for movement
        float animTimer = 0.0f;
        bool wasMoving = false;
        bool wasFacingRight = true;
};

#endif // GAMEOBJECT_HPP
