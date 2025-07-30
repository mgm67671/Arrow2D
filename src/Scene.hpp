
#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include "GameObject.hpp"
#include "Renderer.hpp"

/**
 * @class Scene
 * @brief Manages a collection of game objects within a scene.
 *
 * The Scene class is responsible for storing, updating, animating, and rendering
 * a set of GameObject instances. It takes ownership of the added game objects,
 * ensuring their proper lifetime management. The scene provides interfaces to
 * add objects, update their state, update their animations, and render them
 * using a provided Renderer.
 *
 * @note The Scene class deletes all owned game objects upon destruction.
 */
class Scene
{
    public:
        /**
         * @brief Adds a game object to the scene.
         *
         * This function takes a pointer to a GameObject and adds it to the scene's collection
         * of objects. The scene takes ownership of the object and is responsible for managing
         * its lifetime.
         *
         * @param obj Pointer to the GameObject to be added to the scene.
         */
        void AddObject(GameObject* obj);
        
       
        /**
         * @brief Updates the scene state.
         * 
         * This function should be called every frame to update the scene logic.
         * 
         * @param dt The time elapsed since the last update, in seconds.
         */
        /**
         * @brief Updates the scene state based on the elapsed time.
         *
         * This function should be called once per frame to advance the simulation,
         * animate objects, process physics, or handle any time-dependent logic.
         *
         * @param dt The time elapsed since the last update call, in seconds.
         */
        void Update(float dt);

        
        /**
         * @brief Updates the animation state of the object.
         * 
         * This function advances the animation based on the elapsed time.
         * 
         * @param dt The time delta in seconds since the last update.
         */
        void UpdateAnim(float dt);
    
        /**
         * @brief Renders the scene using the provided renderer, centering the player.
         *
         * This function draws all scene elements by utilizing the specified Renderer instance.
         * The player is always rendered at the center of the window, and all other objects
         * are offset accordingly to create a camera-follow effect.
         *
         * @param renderer Reference to the Renderer object responsible for drawing the scene.
         */
        void Render(Renderer& renderer);
    
        /**
         * @brief Virtual destructor for the Scene class.
         *
         * Ensures proper cleanup of resources in derived classes when a Scene object is deleted.
         */
        virtual ~Scene();

    protected:
        std::vector<GameObject*> objects; // Owned game objects
};

#endif // SCENE_HPP
