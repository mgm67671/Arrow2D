#include <iostream>
#include "Engine.hpp"

int main()
{
    Engine& engine = Engine::Instance();

    if (!engine.Init("My Game", 1440, 810))
    {
        std::cerr << "Failed to initialize the engine." << std::endl;
        return -1;
    }

    engine.Clean(); 
    return 0;
}