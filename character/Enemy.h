#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
#include "../animation/Animation.h"
#include "../physics/RigidBody.h"
#include "../physics/Collider.h"
#include "../physics/Vector2D.h"

class Enemy: public Character
{
    public:
        Enemy(Properties* props);
        virtual void Draw();
        virtual void Clean();
        virtual void Update(float dt);
    
    private:
        Collider* m_Collider;
        Animation* m_Animation;
        RigidBody* m_RigidBody;
        Vector2D m_LastSafePosition;
};

#endif  // ENEMY_H