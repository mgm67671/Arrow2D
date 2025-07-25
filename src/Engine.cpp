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
    this->title = WINDOW_TITLE;
    this->width = WINDOW_WIDTH;
    this->height = WINDOW_HEIGHT;

    // Use singleton subsystems
    renderer = &Renderer::Instance();
    inputManager = &InputManager::Instance();
    textureManager = &TextureManager::Instance();
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
    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
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

/**
 * @brief Releases resources and cleans up dynamically allocated objects.
 *
 * This function deletes the renderer, input manager, texture manager,
 * and player objects to free up memory and prevent resource leaks.
 * It should be called during the shutdown or cleanup phase of the application.
 */
void Engine::Clean()
{
    delete scene;
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

/**
 * @brief Updates the game state based on input and elapsed time.
 *
 * This function processes input from the user, updates the player's position
 * and animation state based on the input, and handles movement logic.
 *
 * @param dt The time delta since the last update in seconds.
 */
void Engine::Update(double dt)
{
    if (scene)
        scene->Update(static_cast<float>(dt));
}

/**
 * @brief Handles input events and updates the input manager state.
 *
 * This function processes all pending SDL events, such as keyboard and mouse input,
 * and updates the input manager's state accordingly. It also checks for quit events
 * to allow the engine to exit gracefully.
 */
void Engine::HandleEvents()
{
    inputManager->Update();
}

/**
 * @brief Renders the current scene using the renderer.
 *
 * This function clears the renderer, renders all game objects in the scene,
 * and presents the rendered frame to the screen.
 */
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