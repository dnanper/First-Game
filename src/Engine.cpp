#include "Engine.h"
#include "../graphics/TextureManager.h"
#include <iostream>
#include "../physics/Transform.h"
#include "../Character/Phanora.h"
#include "../inputs/Input.h"
#include "../timer/Timer.h"
#include "../camera/Camera.h"
#include "../map/MapParser.h"
#include "../character/Enemy.h"
#include "../factory/ObjectFactory.h"
#include "../bullet/Bullet.h"
#include <vector>

Engine* Engine::s_Instance = nullptr;

bool Engine::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != 0)
    {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }

    SDL_WindowFlags window_flags = (SDL_WindowFlags) (SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

    m_Window = SDL_CreateWindow("MAIN GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, window_flags);
    if ( m_Window == nullptr )
    {
        SDL_Log("Failed to create Window: %s", SDL_GetError());
        return false;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if ( m_Renderer == nullptr )
    {
        SDL_Log("Failed to create Renderer: %s", SDL_GetError());
        return false;        
    }

    if (MapParser::GetInstance()->Load())
    {
        std::cout << "Failed to Load map" << std::endl;
    }

    m_LevelMap = MapParser::GetInstance()->GetMap("BossRoom");

    TextureManager::GetInstance()->Load("player_idle", "image/finaltest.png");
    TextureManager::GetInstance()->Load("player_move", "image/move.png");

    TextureManager::GetInstance()->Load("bullet", "image/bullet.png");

    TextureManager::GetInstance()->Load("enemy_idle", "image/enemy.png");

    TextureManager::GetInstance()->Load("bg", "image/bg.png");

    Properties* props = new Properties("player", 450, 450, 60, 60);
    GameObject* player = ObjectFactory::GetInstance()->CreateObject("PLAYER", props);
    Enemy* enemy = new Enemy(new Properties("enemy", 300, 300, 60 ,60));

    m_GameObjects.push_back(player);
    m_GameObjects.push_back(enemy);

    Camera::GetInstance()->SetTarget(player->GetOrigin());
    return m_IsRunning = true;
}

void Engine::Update()
{
    float dt = Timer::GetInstance()->GetDeltaTime();
    
    for (unsigned int i = 0; i != m_GameObjects.size(); i++)
        m_GameObjects[i]->Update(dt);

    for (auto x : p_bullet_list)
        x->Update(dt);

    Camera::GetInstance()->Update(dt);  
    m_LevelMap->Update();
}

void Engine::Render()
{
    SDL_SetRenderDrawColor( m_Renderer, 124, 218, 254, 255);
    SDL_RenderClear(m_Renderer);
    TextureManager::GetInstance()->Draw("bg", 0, 0, 1920, 1080, 0.5, 0);
    m_LevelMap->Render();

    for (unsigned int i = 0; i != m_GameObjects.size(); i++)
        m_GameObjects[i]->Draw();

    for (auto x : p_bullet_list)
        x->Draw();
    
    SDL_RenderPresent(m_Renderer);
}

void Engine::Events()
{
    Input::GetInstance()->Listen();
}

bool Engine::Clean()
{   
    for (unsigned int i = 0; i != m_GameObjects.size(); i++)
        m_GameObjects[i]->Clean();

    for (auto x : p_bullet_list)
        x->Clean();

    TextureManager::GetInstance()->Clean();
    MapParser::GetInstance()->Clean();
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    IMG_Quit();
    SDL_Quit();
}

void Engine::Quit()
{
    m_IsRunning = false;
}