#include "Player.hpp"
#include "TextureManager.hpp"
#include "GameConfig.hpp"
#include <cmath>

Player::Player(float x, float y, float width, float height, const std::unordered_map<AnimState, std::string>& texturePaths, TextureManager* textureManager, SDL_Renderer* renderer)
    : GameObject(x, y, width, height, {}), speed(PLAYER_SPEED)
{
    // Load textures for each animation state from file paths
    std::unordered_map<AnimState, SDL_Texture*> loadedTextures;
    for (const auto& [state, path] : texturePaths)
        loadedTextures[state] = textureManager->LoadTexture(path, renderer);
    this->textures = loadedTextures;
}

void Player::Update(float dt)
{
    // Handle input and movement
    InputManager& input = InputManager::Instance();
    HandleInput(input, dt);
    GameObject::Update(dt);
}

void Player::HandleInput(InputManager& inputManager, float dt)
{
    float vx, vy;
    inputManager.GetMovementVector(vx, vy, speed);
    SetVX(vx);
    SetVY(vy);
    bool moving = (vx != 0.0f || vy != 0.0f);
    bool facingRight = (vx > 0) || (vx == 0 && (GetAnimState() == AnimState::IdleRight || GetAnimState() == AnimState::WalkRightA || GetAnimState() == AnimState::WalkRightB));
    UpdateAnim(dt, moving, facingRight);
}

void Player::UpdateAnim(float dt, bool moving, bool facingRight)
{
    GameObject::UpdateAnim(dt, moving, facingRight);
}

void Player::SetSpeed(float s)
{
    speed = s;
}

float Player::GetSpeed() const
{
    return speed;
}

