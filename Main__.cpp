// g++ -Llib -o MProgram Main__.cpp src/Engine.cpp graphics/TextureManager.cpp physics/Vector2D.h physics/Transform.h 
//object/IObject.h  object/GameObject.h character/Character.h character/Phanora.cpp animation/Animation.cpp inputs/Input.cpp
//physics/RigidBody.h timer/Timer.cpp -lSDL2 -lSDL2_image
#include "src/Engine.h"
#include "timer/Timer.h"

#undef main

int main(int agrc, char** argv)
{
    Engine::GetInstance()->Init();

    while (Engine::GetInstance()->IsRunning())
    {
        Engine::GetInstance()->Events();
        Engine::GetInstance()->Update();
        Engine::GetInstance()->Render();
        Timer::GetInstance()->Tick();
    }

    Engine::GetInstance()->Clean();

    return 0;
}

