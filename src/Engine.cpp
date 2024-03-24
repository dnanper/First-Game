#include "Engine.h"
#include "../graphics/TextureManager.h"
#include "../sounds/Sound.h"
#include "../text/Text.h"
#include <iostream>
#include "../physics/Transform.h"
#include "../Character/Phanora.h"
#include "../inputs/Input.h"
#include "../timer/Timer.h"
#include "../camera/Camera.h"
#include "../map/MapParser.h"
#include "../character/Enemy.h"
//#include "../factory/ObjectFactory.h"
#include "../bullet/Bullet.h"
#include "../collision/CollisionHandler.h"
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

    if (!MapParser::GetInstance()->Load())
    {
        std::cout << "Failed to Load map" << std::endl;
    }

    if (TTF_Init() == -1 )
    {
        std::cout << "Could not initailize SDL2 tff: " << TTF_GetError() << "\n"; 
    }

    m_LevelMap = MapParser::GetInstance()->GetMap("BossRoom");


// Load texture
    TextureManager::GetInstance()->Load("player_idle", "image/finaltest.png");
    TextureManager::GetInstance()->Load("player_move", "image/move.png");

    TextureManager::GetInstance()->Load("bullet", "image/bullet.png");
    TextureManager::GetInstance()->Load("e_bullet", "image/e_bullet.png");
    TextureManager::GetInstance()->Load("e_bullet2", "image/laze.png");

    TextureManager::GetInstance()->Load("enemy_idle", "image/enemy.png");
    TextureManager::GetInstance()->Load("enemy_idle2", "image/enemy_2.png");
    TextureManager::GetInstance()->Load("enemy_idle3", "image/enemy_3.png");
    TextureManager::GetInstance()->Load("enemy_die", "image/explorsion.png");

    TextureManager::GetInstance()->Load("bg", "image/bg.png");
    TextureManager::GetInstance()->Load("portal", "image/portal.png");
//

// Load sounds
    Sound::GetInstance()->LoadEffect("shoot", "audio/gun.mp3");
    Sound::GetInstance()->LoadEffect("e_dead", "audio/enemy_dead2.wav");
// Load Text
    SDL_Color mark_color= {255,255,255};
    Text* mark = new Text("Mark", Font, mark_color );
    m_TextMap.push_back(mark);
//
    //Properties* props = new Properties("player", 450, 450, 60, 60);
    player = new Phanora(new Properties("player", 450, 450, 60, 60));

    Camera::GetInstance()->SetTarget(player->GetOrigin());
    return m_IsRunning = true;
}

void Engine::Update()
{
    float dt = Timer::GetInstance()->GetDeltaTime();
    //std::cout << time << std::endl;
    //std::cout << "health: " << player->getHealth() << std::endl;
    if ( !boss ) time++;
    // spawn enemy
    if ( time == ENEMY_DELAY )
    {
    //    std::cout << " Create new enemy\n";
    //type 1
        Enemy* enemy = new Enemy(new Properties("enemy", 1350, 1350, 60 ,60));
        enemy->setType("enemy_idle");
        m_enemy_list.push_back({enemy, "enemy_idle"});
    //type 2
        Enemy* enemy2 = new Enemy(new Properties("enemy", 1300, 1300, 60 ,60));
        enemy2->setType("enemy_idle2");
        m_enemy_list.push_back({enemy2, "enemy_idle2"});
    //type 3
        int cnt = 0;
        for ( auto &x : type3_pos_list )
        {
            if ( x.second == 0 )
            {
                Enemy* enemy3 = new Enemy(new Properties("enemy", 1350, 1350, 60, 60));
                enemy3->setType("enemy_idle3");
                m_enemy_list.push_back({enemy3, "enemy_idle3"});
                x.second = 1;
                enemy3->type3_pos = cnt;
                //std::cout << "cnt: " << cnt << "-----------------------------"<< std::endl;
                break;
            }
            cnt++;
        }
        cnt = 0;
    
        time = 0;
    }

    if ( m_enemy_list.size() == BOSS_TIME*2 )
        boss = 1;

    if (boss)
    {
        //std::cout << "boss appear!!!" << std::endl;
    }
    
    player->Update(dt);
    for (unsigned int i = 0; i != m_enemy_list.size(); i++)
    {
        m_enemy_list[i].first->Update(dt);
        //std::cout << m_enemy_list[i].second << std::endl;
    }
    for (auto x : p_bullet_list)
        x.first->Update(dt);

    // check bullet-enemy collision
    for ( auto e = m_enemy_list.begin(); e != m_enemy_list.end(); e++)
    {
        for ( auto b = p_bullet_list.begin(); b != p_bullet_list.end(); b++)
        {
            if ( (*b).second == "bullet" )
            {
                if (CollisionHandler::GetInstance()->CheckCollision( (*e).first->getCollider()->Get(), (*b).first->getCollider()->Get() ))
                {
                    (*e).first->e_health -= B_DAME;
                    if ( (*e).first->e_health == 0)
                    {
                        (*e).first->setIsBlown();
                    }
                    (*b).first->setIsDead();
                    mark++;
                }
            }
            // else if ( (*b).second == "e_bullet2" && (*b).first->getTimeEx() == 50 )
            // {
            //     (*b).first->setIsDead();
            // }
        }
    }
    // check e_bullet-player collision
    for ( auto b = p_bullet_list.begin(); b != p_bullet_list.end(); b++)
    {
        if ( (*b).second == "e_bullet" )
        {
            if (CollisionHandler::GetInstance()->CheckCollision( player->GetCollider()->Get(), (*b).first->getCollider()->Get() ))
            {
                player->setHealth(-B_DAME);
                (*b).first->setIsDead();
            }
        }
        else if ( (*b).second == "e_bullet2" )
        {
            if (CollisionHandler::GetInstance()->CheckCollision( player->GetCollider()->Get(), (*b).first->getCollider()->Get() ))
            {
                player->setHealth(-B_DAME_2);
                (*b).first->setIsDead();
            }
        }
    }
    // check enemy1-player collision
    for ( auto e = m_enemy_list.begin(); e != m_enemy_list.end(); e++)
    {
        if ( (*e).second == "enemy_idle")
        {
            if (CollisionHandler::GetInstance()->CheckCollision( player->GetCollider()->Get(), (*e).first->getCollider()->Get() ))
            {
                player->setHealth(-B_DAME_2);
            }
        }
    }
    // check enemy_dead
    for (auto x = m_enemy_list.begin(); x != m_enemy_list.end(); )
    {
        if ( (*x).first->getIsDead() )
        {
            if ( (*x).second == "enemy_idle3" )
            {
                int k = (*x).first->type3_pos;
                int i = 0;
                for (auto &type : type3_pos_list)
                {
                    if ( i == k )
                    {
                        //std::cout <<
                        type.second = 0;
                        break;
                    }
                    i++;
                }                
            }
            m_enemy_list.erase(x);
            //Sound::GetInstance()->PlayEffect("e_dead");
        }
        else
            x++;
    }
    // check bullet_dead
    for (auto x = p_bullet_list.begin(); x != p_bullet_list.end(); )
    {
        if ( (*x).first->getIsDead() )
            p_bullet_list.erase(x);
        else
            x++;
    }
    // check player dead
    if ( player->getHealth() < 0 )
    {
        GameOver = true;
    }
    Camera::GetInstance()->Update(dt);  
    m_LevelMap->Update();
}

void Engine::Render()
{
    SDL_SetRenderDrawColor( m_Renderer, 124, 218, 254, 255);
    SDL_RenderClear(m_Renderer);
    TextureManager::GetInstance()->Draw("bg", 0, 0, 2700, 2700, 1, 0);
    TextureManager::GetInstance()->Draw("portal",1068, 1138, 564, 423, 1, 0);
    m_LevelMap->Render();

    player->Draw();
    for (unsigned int i = 0; i != m_enemy_list.size(); i++)
        m_enemy_list[i].first->Draw();

    for (auto x : p_bullet_list)
        x.first->Draw();
    
    SDL_RenderPresent(m_Renderer);
}

void Engine::Events()
{
    Input::GetInstance()->Listen();
}

bool Engine::Clean()
{   
    player->Clean();
    for (unsigned int i = 0; i != m_enemy_list.size(); i++)
        m_enemy_list[i].first->Clean();

    for (auto x : p_bullet_list)
        x.first->Clean();

    TextureManager::GetInstance()->Clean();
    Sound::GetInstance()->Clean();
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