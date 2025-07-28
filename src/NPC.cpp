#include "NPC.hpp"
#include "TextureManager.hpp"


NPC::NPC(float x, float y, float width, float height, const std::unordered_map<AnimState, std::string>& textures, float speed, TextureManager* textureManager, SDL_Renderer* renderer)
    : GameObject(x, y, width, height, std::unordered_map<AnimState, SDL_Texture*>())
{
    std::unordered_map<AnimState, SDL_Texture*> loadedTextures;
    for (const auto& pair : textures) 
        loadedTextures[pair.first] = textureManager->LoadTexture(pair.second, renderer);
    this->textures = loadedTextures;
}

void NPC::Update(float deltaTime)
{
    // Basic NPC logic (idle for now)
    // You can add AI or movement here later
    GameObject::Update(deltaTime);
}