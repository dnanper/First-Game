#ifndef BULLET_H
#define BULLET_H

#include "../animation/Animation.h"
#include "../physics/RigidBody.h"
#include "../physics/Collider.h"
#include "../physics/Vector2D.h"
#include "../character/Character.h"
#include <vector>

#define PI 3.14159265358979323846
#define B_SPEED 8

class Bullet : public Character
{
    public:
        Bullet(Properties* props);
        ~Bullet() {}

        virtual void Draw();
        virtual void Update(float dt);
        virtual void Clean();

        double p_angle;

        RigidBody* p_RigidBody;
        void Set_xpos(int x) { x_pos = x; }
        void Set_ypos(int y) { y_pos = y; }

    private:
        double x_pos;
        double y_pos;

        Collider* m_Collider;
        Animation* m_Animation;
        RigidBody* m_RigidBody;
        Vector2D m_LastSafePosition;
};

#endif  // BULLET_H
