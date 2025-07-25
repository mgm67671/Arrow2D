#include "Scene.hpp"

void Scene::AddObject(GameObject* obj)
{
    objects.push_back(obj);
}

void Scene::Update(float dt)
{
    for (auto obj : objects)
        obj->Update(dt);
}

void Scene::UpdateAnim(float dt)
{
    for (auto obj : objects)
        obj->UpdateAnim(dt, obj->GetVX() != 0.0f || obj->GetVY() != 0.0f, obj->GetVX() >= 0.0f);
}

void Scene::Render(Renderer& renderer)
{
    for (auto obj : objects)
        renderer.Render(*obj);
}

Scene::~Scene()
{
    for (auto obj : objects)
        delete obj;
}
