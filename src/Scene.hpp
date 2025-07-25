
#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include "GameObject.hpp"
#include "Renderer.hpp"

/**
 * @class Scene
 * @brief Manages a collection of game objects and coordinates their update and rendering.
 *
 * The Scene class is responsible for storing, updating, and rendering all game objects
 * that are part of a particular scene (level, menu, etc.). It provides methods to add objects,
 * update their state, and render them using the provided renderer.
 */
class Scene
{
    public:
        /**
         * @brief Adds a game object to the scene.
         * @param obj Pointer to the GameObject to add. Scene takes ownership.
         */
        void AddObject(GameObject* obj);

        /**
         * @brief Updates all game objects in the scene.
         * @param dt Time delta since last update (in seconds).
         */
        void Update(float dt);

        /**
         * @brief Updates animation state for all game objects in the scene.
         * @param dt Time delta since last update (in seconds).
         */
        void UpdateAnim(float dt);

        /**
         * @brief Renders all game objects in the scene using the provided renderer.
         * @param renderer Reference to the Renderer.
         */
        void Render(Renderer& renderer);

        /**
         * @brief Destructor. Cleans up all game objects owned by the scene.
         */
        ~Scene();
    private:
        std::vector<GameObject*> objects; ///< All game objects in the scene.
};

#endif // SCENE_HPP
