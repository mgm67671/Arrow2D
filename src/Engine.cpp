#include <iostream>
#include "Renderer.hpp"
#include "InputManager.hpp"
#include "TextureManager.hpp"
#include "Engine.hpp"

// Singleton instance accessor
Engine& Engine::Instance()
{
    static Engine instance;
    return instance;
}

/**
 * @brief Initializes the engine with the specified window title and dimensions.
 *
 * This function sets the window title, width, and height for the engine,
 * and marks the engine as running.
 *
 * @param title The title of the window.
 * @param width The width of the window in pixels.
 * @param height The height of the window in pixels.
 * @return true if initialization was successful, false otherwise.
 */
bool Engine::Init(const char* title, int width, int height)
{
    this->title = title;
    this->width = width;
    this->height = height;

    // Use singleton subsystems
    renderer = &Renderer::Instance();
    inputManager = &InputManager::Instance();
    textureManager = &TextureManager::Instance();
    if (!renderer || !inputManager || !textureManager)
    {
        std::cerr << "Failed to initialize a core subsystem." << std::endl;
        return false;
    }

    SDL_Window* window = SDL_CreateWindow(title, width, height, 0);
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

    player = new GameObject(100.0f, 100.0f, textureManager->LoadTexture("../../assets/player.bmp", renderer->GetSDLRenderer()));
    if (!player)
    {
        std::cerr << "Failed to allocate player object." << std::endl;
        SDL_DestroyWindow(window);
        return false;
    }

    running = true;
    Run();
    SDL_DestroyWindow(window);
    return true;
}

/**
 * @brief Releases resources and cleans up dynamically allocated objects.
 *
 * This function deletes the renderer, input manager, texture manager,
 * and player objects to free up memory and prevent resource leaks.
 * It should be called during the shutdown or cleanup phase of the application.
 */
void Engine::Clean()
{
    delete player;
}

/**
 * @brief Main loop of the engine.
 *
 * Continuously runs while the engine is active. In each iteration,
 * it handles input events, updates the game state, and renders the scene.
 * The loop exits when the 'running' flag is set to false.
 */
void Engine::Run()
{
    while (running)
    {
        HandleEvents();
        Update();
        Render();
    }
}

/**
 * @brief Updates the game state.
 *
 * This is a placeholder implementation. You should expand this method
 * to update your game objects and logic as needed.
 */
void Engine::Update()
{
    // TODO: Add game update logic here
}

/**
 * @brief Handles input events and updates the running state.
 *
 * This is a placeholder implementation. You should expand this method
 * to process actual input events as needed for your application.
 */
void Engine::HandleEvents()
{
    inputManager->Update();
}

/**
 * @brief Renders the current game scene.
 *
 * This is a placeholder implementation. You should expand this method
 * to render your game objects as needed.
 */
void Engine::Render()
{
    // TODO: Add rendering logic here
}


//Setters


void Engine::SetRunning(bool state)
{
    running = state;
}