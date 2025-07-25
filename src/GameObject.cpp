#include "GameObject.hpp"

void GameObject::SetVelocity(float vx, float vy)
{
    this->vx = vx;
    this->vy = vy;
}

float GameObject::GetVX() const { return vx; }
float GameObject::GetVY() const { return vy; }

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
GameObject::GameObject(float x, float y, SDL_Texture *texture) : x(x), y(y), vx(0), vy(0), texture(texture)
{
    // Initialize any other necessary variables or states here
}

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
    // Render the texture at the object's position
    SDL_FRect destRect = { x, y, 64.0f, 64.0f }; // Example size
    SDL_RenderTexture(renderer, texture, nullptr, &destRect);
}

SDL_Texture *GameObject::GetTexture()
{
    return texture;
}

SDL_FRect GameObject::GetDestRect() const
{
    return { x, y, 64.0f, 64.0f }; // Example size, adjust as needed
}