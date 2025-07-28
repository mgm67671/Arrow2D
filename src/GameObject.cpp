#include "GameObject.hpp"
#include "GameConfig.hpp"

GameObject::GameObject(float x, float y, const std::unordered_map<AnimState, SDL_Texture*>& textures)
    : x(x), y(y), vx(0), vy(0), textures(textures), animState(AnimState::IdleLeft), animTimer(0.0f), wasFacingRight(true), wasMoving(false) {}

void GameObject::Update(float dt)
{
    // Update position based on velocity and delta time
    this->dt = dt;
    x += vx * dt;
    y += vy * dt;
}

void GameObject::Render(SDL_Renderer *renderer, float offsetX, float offsetY)
{
    // Render the current animation state's texture at the object's position, applying camera offset
    SDL_FRect destRect = { x - offsetX, y - offsetY, PLAYER_HOR_SIZE, PLAYER_VER_SIZE };
    SDL_Texture* tex = nullptr;
    if (textures.count(animState))
        tex = textures.at(animState);
    if (tex)
        SDL_RenderTexture(renderer, tex, nullptr, &destRect);
}

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
    wasMoving = moving;
    wasFacingRight = facingRight;
}

SDL_Texture *GameObject::GetTexture() const 
{ 
    // Return the texture for the current animation state, or nullptr if not found
    auto it = textures.find(animState);
    if (it == textures.end())
        return nullptr;
    return it->second;
}

SDL_FRect GameObject::GetDestRect() const { return { x, y, PLAYER_HOR_SIZE, PLAYER_VER_SIZE }; }
float GameObject::GetVX() const { return vx; }
float GameObject::GetVY() const { return vy; }
float GameObject::GetX() const { return x; }
float GameObject::GetY() const { return y; }
AnimState GameObject::GetAnimState() const { return animState; }

void GameObject::SetVX(float vx) { this->vx = vx; }
void GameObject::SetVY(float vy) { this->vy = vy; }
void GameObject::SetX(float x) { this->x = x; }
void GameObject::SetY(float y) { this->y = y; }
void GameObject::SetAnimState(AnimState state) { animState = state; }
