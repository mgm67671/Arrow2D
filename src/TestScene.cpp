
#include "TestScene.hpp"
#include "TextureManager.hpp"
#include <iostream>
#include "GameConfig.hpp"

// Data-driven scene definition
const std::vector<GameObjectDef> TestScene::testSceneObjects = 
{
    {
        "Player",
        (WINDOW_WIDTH / 2) - 32, (WINDOW_HEIGHT / 2) - 32, // Example centered position for 960x540 window
        {
            {AnimState::IdleLeft,   "assets/sprites/Player/Left_Idle.bmp"},
            {AnimState::IdleRight,  "assets/sprites/Player/Right_Idle.bmp"},
            {AnimState::WalkLeftA,  "assets/sprites/Player/Moving_Left_A.bmp"},
            {AnimState::WalkLeftB,  "assets/sprites/Player/Moving_Left_B.bmp"},
            {AnimState::WalkRightA, "assets/sprites/Player/Moving_Right_A.bmp"},
            {AnimState::WalkRightB, "assets/sprites/Player/Moving_Right_B.bmp"}
        }
    }
};

TestScene::TestScene(Renderer& renderer, TextureManager& textureManager, int winWidth, int winHeight)
{
    // Construct objects from the static data array
    for (const auto& def : testSceneObjects)
    {
        if (def.type == "Player")
        {
            auto player = new Player(def.x, def.y, def.texturePaths, PLAYER_SPEED, &textureManager, renderer.GetSDLRenderer());
            AddObject(player);
        }
    }
}
