#include "GameObject.hpp"

/**
 * @brief Constructs a new GameObject at the specified position with the given texture.
 *
 * Initializes the GameObject's position to (x, y), sets the initial velocity (vx, vy) to zero,
 * and assigns the provided SDL_Texture pointer to the texture member.
 *
 * @param x The initial x-coordinate of the GameObject.
 * @param y The initial y-coordinate of the GameObject.
 * @param texture Pointer to the SDL_Texture to be used for rendering this GameObject.
 */

GameObject::GameObject(float x, float y, const std::unordered_map<AnimState, SDL_Texture*>& textures) : x(x), y(y), vx(0), vy(0), textures(textures), animState(AnimState::IdleLeft), animTimer(0.0f), lastFacingRight(true), wasMoving(false), wasFacingRight(true) {}

/**
 * @brief Updates the position of the game object based on its velocity and the elapsed time.
 * 
 * @param dt The time delta (in seconds) since the last update.
 * 
 * This function updates the object's internal time delta and increments its
 * position (x, y) according to its velocity (vx, vy) and the elapsed time.
 */
void GameObject::Update(float dt)
{
    this->dt = dt;
    x += vx * dt;
    y += vy * dt;
}

/**
 * @brief Renders the game object using the specified SDL renderer.
 *
 * @param renderer Pointer to the SDL_Renderer used for drawing the game object.
 */
void GameObject::Render(SDL_Renderer *renderer)
{
    SDL_FRect destRect = { x, y, 64.0f, 64.0f };
    SDL_Texture* tex = textures.count(animState) ? textures.at(animState) : nullptr;
    if (tex)
        SDL_RenderTexture(renderer, tex, nullptr, &destRect);
}

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
void GameObject::UpdateAnim(float dt, bool moving, bool facingRight)
{
    animTimer += dt;
    const float animFrameTime = 0.10f;
    if (!moving)
    {
        if (facingRight)
            animState = AnimState::IdleRight;
        else
            animState = AnimState::IdleLeft;
        animTimer = 0.0f;
    }
    else
    {
        if (!wasMoving || wasFacingRight != facingRight)
            animTimer = 0.0f; // Reset timer when starting to move or changing direction
        if (animTimer >= animFrameTime)
        {
            // Toggle frame
            if (facingRight)
            {
                if (animState == AnimState::WalkRightA)
                    animState = AnimState::WalkRightB;
                else
                    animState = AnimState::WalkRightA;
            }
            else
            {
                if (animState == AnimState::WalkLeftA)
                    animState = AnimState::WalkLeftB;
                else
                    animState = AnimState::WalkLeftA;
            }
            animTimer = 0.0f;
        }
        else
        {
            // Keep current frame
            if (facingRight && (animState != AnimState::WalkRightA && animState != AnimState::WalkRightB))
                animState = AnimState::WalkRightA;
            if (!facingRight && (animState != AnimState::WalkLeftA && animState != AnimState::WalkLeftB))
                animState = AnimState::WalkLeftA;
        }
    }
    lastFacingRight = facingRight;
    wasMoving = moving;
    wasFacingRight = facingRight;
}

SDL_Texture *GameObject::GetTexture() { return textures.count(animState) ? textures.at(animState) : nullptr; }
SDL_FRect GameObject::GetDestRect() const { return { x, y, 64.0f, 64.0f }; }
float GameObject::GetVX() const { return vx; }
float GameObject::GetVY() const { return vy; }
void GameObject::SetVelocity(float vx, float vy) { this->vx = vx; this->vy = vy; }

void GameObject::SetAnimState(AnimState state) { animState = state; }
AnimState GameObject::GetAnimState() const { return animState; }
