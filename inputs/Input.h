#ifndef INPUT_H
#define INPUT_H

#include "../inc/SDL.h"

enum Axis { HORIZONTAL, VERTICAL};

class Input
{
    public:
        static Input* GetInstance()
        {
            return s_Instance = (s_Instance != nullptr)? s_Instance : new Input();
        }

        void Listen();
        bool GetKeyDown(SDL_Scancode key);
        int GetMouseX();
        int GetMouseY();
        bool GetMouseCheck();
        int GetAxisKey(Axis axis);
        int x_mouse, y_mouse;
        bool mousecheck = 0;

    private:
        Input();
        void KeyUp();
        void KeyDown();
        void MouseMotion();
        void MouseDown();
        void MouseUp();
        
        const Uint8* m_KeyStates;
        static Input* s_Instance;
};

#endif  // INPUT_H