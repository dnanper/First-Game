#ifndef PHANORA_H
#define PHANORA_H

#include "Character.h"
#include "../animation/Animation.h"
#include "../physics/RigidBody.h"

class Phanora : public Character
{
    public:
        Phanora(Properties* props);

        virtual void Draw();
        virtual void Update(float dt);
        virtual void Clean();
    
    private:
        // int m_Row, m_Frame, m_FrameCount;
        // int m_AnimSpeed;
        
        Animation* m_Animation;
        RigidBody* m_RigidBody;
};

#endif  // PHANORA_H