#ifndef TEST_SCENE_HPP
#define TEST_SCENE_HPP

#include "Scene.hpp"
#include "Player.hpp"
#include <memory>
#include <vector>
#include <unordered_map>

/**
 * @struct GameObjectDef
 * @brief Defines a game object for data-driven scene construction.
 *
 * This struct allows the scene to be defined by data, making it easy to add new object types and properties.
 */
struct GameObjectDef
{
    std::string type; // Object type (e.g., "Player")
    float x, y; // Initial position

    /// @brief Maps each animation state to its corresponding texture file path.
    /// @details
    /// This unordered_map associates an AnimState (representing a specific animation state)
    /// with a std::string containing the file path to the texture used for that state.
    /// It enables efficient retrieval of texture resources based on the current animation state.
    std::unordered_map<AnimState, std::string> texturePaths; 
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
         * @brief Constructs a TestScene object.
         * 
         * Initializes the test scene with the provided renderer, texture manager, and window dimensions.
         * 
         * @param renderer Reference to the Renderer used for drawing scene elements.
         * @param textureManager Reference to the TextureManager for managing textures in the scene.
         * @param winWidth Width of the window in pixels.
         * @param winHeight Height of the window in pixels.
         */
        TestScene(Renderer& renderer, TextureManager& textureManager, int winWidth, int winHeight);
        
        
        /// @brief Default destructor for the TestScene class.
        /// @details This destructor does not perform any custom cleanup, as it is defaulted.
        ~TestScene() = default;

    private:
        /**
         * @brief A static constant vector containing definitions of game objects for the test scene.
         *
         * This vector holds instances of GameObjectDef, each representing the configuration
         * and properties of a game object to be included in the test scene. It is intended
         * to be used for initializing or referencing the objects present in the scene.
         */
        static const std::vector<GameObjectDef> testSceneObjects;
};

#endif // TEST_SCENE_HPP