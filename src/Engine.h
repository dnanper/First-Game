#ifndef ENGINE_H
#define ENGINE_H

#include "../inc/SDL.h"
#include "../inc/SDL_image.h"
#include "../map/GameMap.h"
#include "../object/GameObject.h"  
#include "../bullet/Bullet.h"
#include <vector>
// #include "../state/GameState.h"


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
        std::vector<Bullet*> p_bullet_list;

    private:
        Engine(){}
        bool m_IsRunning;
        GameMap* m_LevelMap;
        SDL_Window* m_Window;
        SDL_Renderer* m_Renderer;
        static Engine* s_Instance;
        //std::vector<GameState*> m_States;
        std::vector<GameObject*> m_GameObjects;
};

#endif  // ENGINE_H