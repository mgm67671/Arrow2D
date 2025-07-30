#include "Scene.hpp"
#include "Player.hpp"
#include "Renderer.hpp"
#include "GameConfig.hpp"

void Scene::AddObject(GameObject* obj)
{
    // Add a new game object to the scene (Scene takes ownership)
    objects.push_back(obj);
}

void Scene::Update(float dt)
{
    // Update all game objects in the scene with per-axis collision checks
    for (auto obj : objects) 
    {
        // Check X movement
        float tryX = obj->GetX() + obj->GetVX() * dt;
        SDL_FRect hitboxX = obj->GetHitbox();
        hitboxX.x = tryX;
        bool collisionX = false;
        for (auto other : objects) 
        {
            if (other == obj) 
                continue;
            if (GameObject::Intersects(hitboxX, other->GetHitbox())) 
            {
                collisionX = true;
                break;
            }
        }
        if (!collisionX)
            obj->SetX(tryX);

        // Check Y movement
        float tryY = obj->GetY() + obj->GetVY() * dt;
        SDL_FRect hitboxY = obj->GetHitbox();
        hitboxY.y = tryY;
        bool collisionY = false;
        for (auto other : objects) 
        {
            if (other == obj) continue;
            if (GameObject::Intersects(hitboxY, other->GetHitbox())) 
            {
                collisionY = true;
                break;
            }
        }
        if (!collisionY)
            obj->SetY(tryY);

        // Update hitbox to new position
        SDL_FRect newHitbox = obj->GetHitbox();
        newHitbox.x = obj->GetX();
        newHitbox.y = obj->GetY();
        obj->SetHitbox(newHitbox);

        obj->Update(dt); // update everything else (including animation)
    }
}

void Scene::UpdateAnim(float dt)
{
    // Update animation state for all game objects
    for (auto obj : objects)
        obj->UpdateAnim(dt, obj->GetVX() != 0.0f || obj->GetVY() != 0.0f, obj->GetVX() >= 0.0f);
}

void Scene::Render(Renderer& renderer)
{
    // Find the player (assumes only one Player in objects)
    GameObject* player = nullptr;
    for (auto obj : objects) 
    {
        if (dynamic_cast<class Player*>(obj)) 
        {
            player = obj;
            break;
        }
    }
    float offsetX = 0.0f, offsetY = 0.0f;
    if (player) 
    {
        // Center the player in the window
        int winW = 960, winH = 540; // Default fallback
        SDL_Renderer* sdlRenderer = renderer.GetSDLRenderer();
        if (sdlRenderer) 
            SDL_GetCurrentRenderOutputSize(sdlRenderer, &winW, &winH);
        offsetX = player->GetX() - (winW / 2.0f) + (PLAYER_HOR_SIZE / 2.0f);
        offsetY = player->GetY() - (winH / 2.0f) + (PLAYER_VER_SIZE / 2.0f);
    }
    // Render all game objects with camera offset
    for (auto obj : objects)
        renderer.Render(*obj, offsetX, offsetY);
}

Scene::~Scene()
{
    // Delete all owned game objects
    for (auto obj : objects)
        delete obj;
}
