#include "Phanora.h"
#include "../graphics/TextureManager.h"
#include "../inc/SDL.h"
#include "../inputs/Input.h"

Phanora::Phanora(Properties* props): Character(props)
{
    m_Animation = new Animation();
    m_RigidBody = new RigidBody();
    m_Animation->SetProps(m_TextureID, 1, 6, 120);
}

void Phanora::Draw()
{
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
}

void Phanora::Update(float dt)
{
    m_Animation->SetProps("player", 1, 6, 120);
    m_RigidBody->UnSetForce();

    if ( Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A) )
    {
        m_RigidBody->ApplyForceX(5*BACKWARD);
        m_Animation->SetProps("player_move", 1, 6, 120);
    }

    if ( Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D) )
    {
        m_RigidBody->ApplyForceX(5*FORWARD);
        m_Animation->SetProps("player_move", 1, 6, 120, SDL_FLIP_HORIZONTAL);
    }

    if ( Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W) )
    {
        m_RigidBody->ApplyForceY(5*UPWARD);
        m_Animation->SetProps("player_move", 1, 6, 120);
    }

    if ( Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S) )
    {
        m_RigidBody->ApplyForceY(5*DOWNWARD);
        m_Animation->SetProps("player_move", 1, 6, 120, SDL_FLIP_VERTICAL);
    }

    m_RigidBody->Update(0.4);
    m_Transform->TranslateX(m_RigidBody->Position().X);
    m_Transform->TranslateY(m_RigidBody->Position().Y);
    m_Animation->Update();
}

void Phanora::Clean()
{
    TextureManager::GetInstance()->Clean();
}
