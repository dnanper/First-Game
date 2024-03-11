#include "Phanora.h"
#include "../graphics/TextureManager.h"
#include "../inc/SDL.h"
#include "../inputs/Input.h"
#include "../src/Engine.h"
#include "../camera/Camera.h"
#include "../collision/CollisionHandler.h"
#include "../factory/ObjectFactory.h"
#include "../bullet/Bullet.h"
#include <math.h>

static Registrar<Phanora> registrar("PLAYER");

Phanora::Phanora(Properties* props): Character(props)
{
    m_Collider = new Collider();
    m_Collider->SetBuffer(0,0,0,0);

    m_RigidBody = new RigidBody();

    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 1, 6, 120);
}

void Phanora::Draw()
{
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height, angle);
    // debugger
    /*
    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect box = m_Collider->Get();
    box.x -= cam.X;
    box.y -= cam.Y;
    SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
    */
}

void Phanora::Update(float dt)
{
    m_Animation->SetProps("player_idle", 1, 6, 120);
    m_RigidBody->UnSetForce();

    if ( Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A) )
    {
        m_RigidBody->ApplyForceX(P_SPEED*BACKWARD);
        m_Animation->SetProps("player_move", 1, 6, 120);
    }

    if ( Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D) )
    {
        m_RigidBody->ApplyForceX(P_SPEED*FORWARD);
        m_Animation->SetProps("player_move", 1, 6, 120, SDL_FLIP_NONE);
    }

    if ( Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W) )
    {
        m_RigidBody->ApplyForceY(P_SPEED*UPWARD);
        m_Animation->SetProps("player_move", 1, 6, 120);
    }

    if ( Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S) )
    {
        m_RigidBody->ApplyForceY(P_SPEED*DOWNWARD);
        m_Animation->SetProps("player_move", 1, 6, 120, SDL_FLIP_NONE);
    }

    // SDL_Log("%f", dt);
    // X
    m_RigidBody->Update(dt);
    m_LastSafePosition.X = m_Transform->X;
    m_Transform->X += m_RigidBody->Position().X;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 45, 45);
    
    if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
    {
        m_Transform->X = m_LastSafePosition.X;
    }
    // Y
    m_RigidBody->Update(dt);
    m_LastSafePosition.Y = m_Transform->Y;
    m_Transform->Y += m_RigidBody->Position().Y;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 45, 45);
    
    if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
    {
        m_Transform->Y = m_LastSafePosition.Y;
    }
    // m_Transform->TranslateX(m_RigidBody->Position().X);
    // m_Transform->TranslateY(m_RigidBody->Position().Y);
    // camera
    m_Origin->X = m_Transform->X + m_Width/2;
    m_Origin->Y = m_Transform->Y + m_Height/2;
    //mouse motion
    angle = -90 + atan2( /*m_Transform->Y + m_Height/2*/450 - Input::GetInstance()->GetMouseY(), /*m_Transform->X + m_Width/2*/450 - Input::GetInstance()->GetMouseX() ) * ( 180/PI);
    if ( angle < 0 ) angle = 360 + angle;

    // bullet
    if ( Input::GetInstance()->GetMouseCheck() )
    {
        canspawnbullet = 1;
    }

    if ( !Input::GetInstance()->GetMouseCheck() )
    {
        canspawnbullet = 0;
    }
    CurrentTime=SDL_GetTicks();
    if ( canspawnbullet && ( CurrentTime>LastTime+200) )
    {
        std::cout << "create new bullet\n";
        i++;
        Bullet* p_bullet=new Bullet(new Properties("bullet", 450, 450, 10 ,30));
        p_bullet->p_angle = angle;
        p_bullet->Set_xpos(m_Transform->X + m_Width/2);
        p_bullet->Set_ypos(m_Transform->Y + m_Height/2);
        Engine::GetInstance()->p_bullet_list.push_back(p_bullet);
        LastTime = CurrentTime;
        // for (auto x:  Engine::GetInstance()->p_bullet_list)
        // {
        //     std::cout << i << std::endl;
        // }
    }

    m_Animation->Update();
}

void Phanora::Clean()
{
    TextureManager::GetInstance()->Drop(m_TextureID);
}
