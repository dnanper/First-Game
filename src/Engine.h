#ifndef ENGINE_H
#define ENGINE_H

#include "../inc/SDL.h"
#include "../inc/SDL_image.h"
#include "../inc/SDL_mixer.h"
#include "../map/GameMap.h"
#include "../object/GameObject.h"  
#include "../bullet/Bullet.h"
#include "../character/Phanora.h"
#include "../character/Enemy.h"
#include "../text/Text.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>
// #include "../state/GameState.h"

#define ENEMY_DELAY 100
#define BOSS_TIME 50
#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 900

class Engine
{
    public:
        static Engine* GetInstance()
        {
            return s_Instance = (s_Instance != nullptr)? s_Instance : new Engine();
        }

        bool Init();
        bool Clean();
        void Quit();

        void Update();
        void Render();
        void Events();

        // void PopState();
        // void PushState(GameState* current);
        // void ChangeState(GameState* target);

        inline GameMap* GetMap() { return m_LevelMap; }
        inline SDL_Window* GetMainWindow() { return m_Window; }
        inline bool IsRunning()  { return m_IsRunning; }
        inline SDL_Renderer* GetRenderer()  { return m_Renderer; }
        std::vector<std::pair<Bullet*, std::string>> p_bullet_list;
        // std::vector<GameObject*> m_GameObjects;
        std::vector<std::pair<Enemy*, std::string>> m_enemy_list;
        Phanora* player = nullptr;
        std::vector<Text*> m_TextMap;

        std::map<std::pair<int,int>,bool> type3_pos_list = 
        { {{1000, 1350},0}, {{1160, 1175},0}, {{1350,1100},0}, {{1500,1175},0}, {{1630,1350},0}, {{1500,1525},0}, {{1350,1600},0}, {{1160,1525},0} };
        //bool spawnType3 = false;

        TTF_Font *Font = TTF_OpenFont("fonts/VTKSDURA3d.ttf", 10);
        Text* mark = nullptr;

    private:
        Engine(){}
        bool m_IsRunning;
        bool GameOver = 0;
        GameMap* m_LevelMap;
        SDL_Window* m_Window;
        SDL_Renderer* m_Renderer;
        static Engine* s_Instance;

        int mark = 0;

        long long time = 0;
        bool boss = 0;
        //std::vector<GameState*> m_States;
};

#endif  // ENGINE_H