#include "Player.hpp"
#include "TextureManager.hpp"
#include <cmath>


/**
 * @brief Constructs a Player object at the specified position with the given textures and speed.
 * @param x Initial x-coordinate.
 * @param y Initial y-coordinate.
 * @param textures Map of animation states to SDL_Textures.
 * @param speed Movement speed in pixels per second.
 */

Player::Player(float x, float y, const std::unordered_map<AnimState, std::string>& texturePaths, float speed, TextureManager* textureManager, SDL_Renderer* renderer)
    : GameObject(x, y, {}), speed(speed)
{
    std::unordered_map<AnimState, SDL_Texture*> loadedTextures;
    for (const auto& [state, path] : texturePaths)
    {
        loadedTextures[state] = textureManager->LoadTexture(path, renderer);
    }
    this->textures = loadedTextures;
}


/**
 * @brief Updates the player each frame (handles input, movement, and animation).
 * @param dt Time delta since last update (in seconds).
 */
void Player::Update(float dt)
{
    // Handle input and movement
    InputManager& input = InputManager::Instance();
    HandleInput(input, dt);
    GameObject::Update(dt);
}


/**
 * @brief Handles input and updates velocity and animation state.
 * @param inputManager Reference to the InputManager.
 * @param dt Time delta since last update (in seconds).
 */
void Player::HandleInput(InputManager& inputManager, float dt)
{
    float vx, vy;
    inputManager.GetMovementVector(vx, vy, speed);
    SetVelocity(vx, vy);
    bool moving = (vx != 0.0f || vy != 0.0f);
    bool facingRight = (vx > 0) || (vx == 0 && (GetAnimState() == AnimState::IdleRight || GetAnimState() == AnimState::WalkRightA || GetAnimState() == AnimState::WalkRightB));
    UpdateAnim(dt, moving, facingRight);
}


/**
 * @brief Updates the animation state based on movement and direction.
 * @param dt Time delta since last update (in seconds).
 * @param moving Whether the player is moving.
 * @param facingRight Whether the player is facing right.
 */
void Player::UpdateAnim(float dt, bool moving, bool facingRight)
{
    GameObject::UpdateAnim(dt, moving, facingRight);
}


/**
 * @brief Sets the player's movement speed.
 * @param s New speed value.
 */
void Player::SetSpeed(float s)
{
    speed = s;
}

/**
 * @brief Gets the player's movement speed.
 * @return Current speed value.
 */
float Player::GetSpeed() const
{
    return speed;
}

