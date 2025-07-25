

#pragma once
#include "Scene.hpp"
#include "Player.hpp"
#include <memory>
#include <vector>
#include <unordered_map>

/**
 * @struct GameObjectDef
 * @brief Defines a game object for data-driven scene construction.
 */
struct GameObjectDef
{
    std::string type; ///< Object type (e.g., "Player")
    float x, y; ///< Initial position
    std::unordered_map<AnimState, std::string> texturePaths; ///< Animation state to texture path
    float speed = 0.0f; ///< Movement speed (for Player)
    // Add more properties as needed
};

/**
 * @class TestScene
 * @brief A sample scene for testing, sets up the player and initial state.
 *
 * TestScene is a concrete implementation of Scene that sets up the player
 * and any other objects for demonstration or testing purposes.
 */
class TestScene : public Scene 
{
    public:
        /**
         * @brief Constructs the test scene by loading objects from a static data array.
         * @param renderer Reference to the Renderer.
         * @param textureManager Reference to the TextureManager.
         * @param winWidth Window width.
         * @param winHeight Window height.
         */
        TestScene(Renderer& renderer, TextureManager& textureManager, int winWidth, int winHeight);
        ~TestScene() = default;
    private:
        static const std::vector<GameObjectDef> testSceneObjects;
};
