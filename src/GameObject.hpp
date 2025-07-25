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

enum class PlayerAnimState { IdleLeft, IdleRight, WalkLeftA, WalkLeftB, WalkRightA, WalkRightB };

class GameObject
{
public:
    GameObject(float x, float y, const std::unordered_map<PlayerAnimState, SDL_Texture*>& textures);
    void Update(float dt);
    void Render(SDL_Renderer *renderer);
    SDL_Texture *GetTexture();
    SDL_FRect GetDestRect() const;

    void SetVelocity(float vx, float vy);
    float GetVX() const;
    float GetVY() const;

    void SetAnimState(PlayerAnimState state);
    PlayerAnimState GetAnimState() const;
    void UpdateAnim(float dt, bool moving, bool facingRight);

private:
    float x, y;
    float vx, vy;
    float dt; // Delta time for movement
    std::unordered_map<PlayerAnimState, SDL_Texture*> textures;
    PlayerAnimState animState;
    float animTimer = 0.0f;
    bool lastFacingRight = true;
    bool wasMoving = false;
    bool wasFacingRight = true;
};

#endif // GAMEOBJECT_HPP
