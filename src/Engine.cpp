#include <iostream>
#include "Renderer.hpp"
#include "InputManager.hpp"
#include "TextureManager.hpp"
#include "Engine.hpp"
#include "TestScene.hpp"
#include "GameConfig.hpp"

Engine& Engine::Instance()
{
    static Engine instance;
    return instance;
}

bool Engine::Init(const char* title, int width, int height)
{
    this->title = WINDOW_TITLE;
    this->width = WINDOW_WIDTH;
    this->height = WINDOW_HEIGHT;

    // Use singleton subsystems
    renderer = &Renderer::Instance();
    inputManager = &InputManager::Instance();
    textureManager = &TextureManager::Instance();
    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!inputManager)
    {
        std::cerr << "Failed to initialize input manager subsystem." << std::endl;
        return false;
    }
    if (!textureManager)
    {
        std::cerr << "Failed to initialize texture manager subsystem." << std::endl;
        return false;
    }
    if (!window)
    {
        std::cerr << "Failed to create SDL_Window: " << SDL_GetError() << std::endl;
        return false;
    }
    if (!renderer->Init(window))
    {
        std::cerr << "Failed to initialize renderer." << std::endl;
        SDL_DestroyWindow(window);
        return false;
    }

    // Create test scene
    scene = new TestScene(*renderer, *textureManager, WINDOW_WIDTH, WINDOW_HEIGHT);

    running = true;
    Run();
    SDL_DestroyWindow(window);
    return true;
}

void Engine::Clean()
{
    delete scene;
}

void Engine::Run()
{
    Uint64 prevTicks = SDL_GetPerformanceCounter();
    const double freq = (double)SDL_GetPerformanceFrequency();
    while (running)
    {
        Uint64 currTicks = SDL_GetPerformanceCounter();
        double dt = (currTicks - prevTicks) / freq;
        prevTicks = currTicks;

        HandleEvents();
        Update(dt);
        Render();
        SDL_Delay(std::max(0, (int)(1000.0 / FPS - dt * 1000)));
    }
}

void Engine::Update(double dt)
{
    if (scene)
        scene->Update(static_cast<float>(dt));
}

void Engine::HandleEvents()
{
    inputManager->Update();
}

void Engine::Render()
{
    renderer->Clean();
    if (scene)
        scene->Render(*renderer);
    renderer->Present();
}

void Engine::SetRunning(bool state)
{
    running = state;
}