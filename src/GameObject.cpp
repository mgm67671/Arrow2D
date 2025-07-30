#include "GameObject.hpp"
#include "GameConfig.hpp"

GameObject::GameObject(float x, float y, float width, float height, const std::unordered_map<AnimState, SDL_Texture*>& textures)
    : x(x), y(y), width(width), height(height), vx(0), vy(0), textures(textures), animState(AnimState::IdleLeft), animTimer(0.0f), wasFacingRight(true), wasMoving(false)
{
    hitbox = {x, y, width, height};
}

void GameObject::Update(float dt)
{
    // Only update per-frame logic (animation, timers, etc.)
    this->dt = dt;
}

void GameObject::Render(SDL_Renderer *renderer, float offsetX, float offsetY)
{
    // Render the current animation state's texture at the object's position, applying camera offset
    SDL_FRect destRect = { x - offsetX, y - offsetY, width, height };
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

bool GameObject::Intersects(const GameObject& other) const 
{
    return Intersects(this->hitbox, other.hitbox);
}

bool GameObject::Intersects(const SDL_FRect& a, const SDL_FRect& b) 
{
    return (a.x < b.x + b.w && a.x + a.w > b.x &&
            a.y < b.y + b.h && a.y + a.h > b.y);
}

SDL_FRect GameObject::GetDestRect() const { return { x, y, width, height }; }

float GameObject::GetWidth() const { return width; }
float GameObject::GetHeight() const { return height; }
float GameObject::GetVX() const { return vx; }
float GameObject::GetVY() const { return vy; }
float GameObject::GetX() const { return x; }
float GameObject::GetY() const { return y; }
SDL_FRect GameObject::GetHitbox() const { return hitbox; }
AnimState GameObject::GetAnimState() const { return animState; }

void GameObject::SetVX(float vx) { this->vx = vx; }
void GameObject::SetVY(float vy) { this->vy = vy; }
void GameObject::SetX(float x) { this->x = x; }
void GameObject::SetY(float y) { this->y = y; }
void GameObject::SetHitbox(const SDL_FRect& rect) { hitbox = rect; }
void GameObject::SetAnimState(AnimState state) { animState = state; }
