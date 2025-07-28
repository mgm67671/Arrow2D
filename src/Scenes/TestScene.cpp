#include "TestScene.hpp"
#include "../TextureManager.hpp"
#include <iostream>
#include "../GameConfig.hpp"
#include "../NPC.hpp"

// Data-driven scene definition
const std::vector<GameObjectDef> TestScene::testSceneObjects = 
{
    {
        "Player",
        (WINDOW_WIDTH / 2) - PLAYER_HOR_SIZE, (WINDOW_HEIGHT / 2) - PLAYER_VER_SIZE,
        PLAYER_HOR_SIZE, PLAYER_VER_SIZE,
        {
            {AnimState::IdleLeft,   "assets/sprites/Player/Left_Idle.bmp"},
            {AnimState::IdleRight,  "assets/sprites/Player/Right_Idle.bmp"},
            {AnimState::WalkLeftA,  "assets/sprites/Player/Moving_Left_A.bmp"},
            {AnimState::WalkLeftB,  "assets/sprites/Player/Moving_Left_B.bmp"},
            {AnimState::WalkRightA, "assets/sprites/Player/Moving_Right_A.bmp"},
            {AnimState::WalkRightB, "assets/sprites/Player/Moving_Right_B.bmp"}
        },
        PLAYER_SPEED
    },
    {
        "NPC",
        100.0f, 100.0f,
        64.0f, 64.0f, // Example size for NPC
        {
            {AnimState::IdleLeft,   "assets/sprites/Player/Left_Idle.bmp"},
            {AnimState::IdleRight,  "assets/sprites/Player/Right_Idle.bmp"},
            {AnimState::WalkLeftA,  "assets/sprites/Player/Moving_Left_A.bmp"},
            {AnimState::WalkLeftB,  "assets/sprites/Player/Moving_Left_B.bmp"},
            {AnimState::WalkRightA, "assets/sprites/Player/Moving_Right_A.bmp"},
            {AnimState::WalkRightB, "assets/sprites/Player/Moving_Right_B.bmp"}
        },
        200.0f // speed
    }
};

TestScene::TestScene(Renderer& renderer, TextureManager& textureManager, int winWidth, int winHeight)
{
    // Construct objects from the static data array
    for (const auto& def : testSceneObjects)
    {
        if (def.type == "Player")
        {
            auto player = new Player(def.x, def.y, def.width, def.height, def.texturePaths, &textureManager, renderer.GetSDLRenderer());
            AddObject(player);
        }
        else if (def.type == "NPC") 
        {
            auto npc = new NPC(def.x, def.y, def.width, def.height, def.texturePaths, def.speed, &textureManager, renderer.GetSDLRenderer());
            AddObject(npc);
        }
    }
}
