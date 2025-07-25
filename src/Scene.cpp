#include "Scene.hpp"

void Scene::AddObject(GameObject* obj)
{
    // Add a new game object to the scene (Scene takes ownership)
    objects.push_back(obj);
}

void Scene::Update(float dt)
{
    // Update all game objects in the scene
    for (auto obj : objects)
        obj->Update(dt);
}

void Scene::UpdateAnim(float dt)
{
    // Update animation state for all game objects
    for (auto obj : objects)
        obj->UpdateAnim(dt, obj->GetVX() != 0.0f || obj->GetVY() != 0.0f, obj->GetVX() >= 0.0f);
}

void Scene::Render(Renderer& renderer)
{
    // Render all game objects in the scene
    for (auto obj : objects)
        renderer.Render(*obj);
}

Scene::~Scene()
{
    // Delete all owned game objects
    for (auto obj : objects)
        delete obj;
}
