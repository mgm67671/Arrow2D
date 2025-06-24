#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <SDL3/SDL.h>

/**
 * @class GameObject
 * @brief Represents a 2D game object with position, velocity, and texture.
 *
 * The GameObject class encapsulates the basic properties and behaviors of a 2D entity in a game,
 * including its position, velocity, rendering, and texture management.
 */
class GameObject
{
    public:
        GameObject(float x, float y, SDL_Texture *texture);
        void Update(float dt);
        void Render(SDL_Renderer *renderer);
        SDL_Texture *GetTexture();
        SDL_FRect GetDestRect() const;

    private:
        float x, y;
        float vx, vy;
        float dt; // Delta time for movement
        SDL_Texture *texture;
};

#endif // GAMEOBJECT_HPP
