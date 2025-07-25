#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP


#include <SDL3/SDL.h>
#include <unordered_map>
#include <string>

/**
 * @class GameObject
 * @brief Represents a 2D game object with position, velocity, and texture.
 *
 * The GameObject class encapsulates the basic properties and behaviors of a 2D entity in a game,
 * including its position, velocity, rendering, and texture management.
 */

/**
 * @enum AnimState
 * @brief Represents animation states for any game object.
 */
enum class AnimState { IdleLeft, IdleRight, WalkLeftA, WalkLeftB, WalkRightA, WalkRightB };

class GameObject
{
    public:
        GameObject(float x, float y, const std::unordered_map<AnimState, SDL_Texture*>& textures);
        virtual void Update(float dt);
        void Render(SDL_Renderer *renderer);
        SDL_Texture *GetTexture();
        SDL_FRect GetDestRect() const;

        // Position
        void SetPosition(float x, float y);
        float GetX() const;
        float GetY() const;

        // Velocity
        void SetVelocity(float vx, float vy);
        float GetVX() const;
        float GetVY() const;

        // Animation state
        void SetAnimState(AnimState state);
        AnimState GetAnimState() const;
        virtual void UpdateAnim(float dt, bool moving, bool facingRight);

    protected:
        std::unordered_map<AnimState, SDL_Texture*> textures;
        AnimState animState;
        
    private:
        float x, y;
        float vx, vy;
        float dt; // Delta time for movement
        float animTimer = 0.0f;
        bool lastFacingRight = true;
        bool wasMoving = false;
        bool wasFacingRight = true;
};

#endif // GAMEOBJECT_HPP
