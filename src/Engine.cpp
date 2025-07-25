#include <iostream>
#include "Renderer.hpp"
#include "InputManager.hpp"
#include "TextureManager.hpp"
#include "Engine.hpp"

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

    // Load all player textures for animation states
    std::unordered_map<PlayerAnimState, SDL_Texture*> playerTextures;
    playerTextures[PlayerAnimState::IdleLeft] = textureManager->LoadTexture("assets/sprites/Player/Left_Idle.bmp", renderer->GetSDLRenderer());
    playerTextures[PlayerAnimState::IdleRight] = textureManager->LoadTexture("assets/sprites/Player/Right_Idle.bmp", renderer->GetSDLRenderer());
    playerTextures[PlayerAnimState::WalkLeftA] = textureManager->LoadTexture("assets/sprites/Player/Moving_Left_A.bmp", renderer->GetSDLRenderer());
    playerTextures[PlayerAnimState::WalkLeftB] = textureManager->LoadTexture("assets/sprites/Player/Moving_Left_B.bmp", renderer->GetSDLRenderer());
    playerTextures[PlayerAnimState::WalkRightA] = textureManager->LoadTexture("assets/sprites/Player/Moving_Right_A.bmp", renderer->GetSDLRenderer());
    playerTextures[PlayerAnimState::WalkRightB] = textureManager->LoadTexture("assets/sprites/Player/Moving_Right_B.bmp", renderer->GetSDLRenderer());

    // Check for any missing textures
    for (const auto& pair : playerTextures) 
    {
        if (!pair.second) {
            std::cerr << "Failed to load one or more player textures." << std::endl;
            SDL_DestroyWindow(window);
            return false;
        }
    }

    // Center the player in the window (assuming 64x64 sprite size)
    float playerW = 64.0f;
    float playerH = 64.0f;
    float playerX = (width - playerW) / 2.0f;
    float playerY = (height - playerH) / 2.0f;
    player = new GameObject(playerX, playerY, playerTextures);
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
        // Optional: Cap frame rate (e.g., to 240 FPS)
        int FPS = 240;
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
    // Movement speed in pixels per second
    const float speed = 300.0f;
    float vx = 0.0f, vy = 0.0f;

    // WASD or Arrow keys
    if (inputManager->IsKeyDown(SDL_SCANCODE_W) || inputManager->IsKeyDown(SDL_SCANCODE_UP))
        vy -= speed;
    if (inputManager->IsKeyDown(SDL_SCANCODE_S) || inputManager->IsKeyDown(SDL_SCANCODE_DOWN))
        vy += speed;
    if (inputManager->IsKeyDown(SDL_SCANCODE_A) || inputManager->IsKeyDown(SDL_SCANCODE_LEFT))
        vx -= speed;
    if (inputManager->IsKeyDown(SDL_SCANCODE_D) || inputManager->IsKeyDown(SDL_SCANCODE_RIGHT))
        vx += speed;

    // Set player velocity and update position
    if (player)
    {
        player->SetVelocity(vx, vy);
        // Determine direction and movement for animation
        bool moving = (vx != 0.0f || vy != 0.0f);
        bool facingRight = (vx > 0) || (vx == 0 && (player->GetAnimState() == PlayerAnimState::IdleRight || player->GetAnimState() == PlayerAnimState::WalkRightA || player->GetAnimState() == PlayerAnimState::WalkRightB));
        player->UpdateAnim(static_cast<float>(dt), moving, facingRight);
        player->Update(static_cast<float>(dt));
    }
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
    renderer->Clean();
    if (player)
        renderer->Render(*player);
    renderer->Present();
}

void Engine::SetRunning(bool state)
{
    running = state;
}