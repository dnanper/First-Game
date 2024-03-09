#include "Enemy.h"
#include "../graphics/TextureManager.h"
#include "../inc/SDL.h"
#include "../src/Engine.h"
#include "../collision/CollisionHandler.h"
#include "../camera/Camera.h"
#include <iostream>
#include "../factory/ObjectFactory.h"

static Registrar<Enemy> registrar("ENEMY");

Enemy::Enemy(Properties* props): Character(props)
{
    m_Collider = new Collider();
    m_Collider->SetBuffer(0,0,0,0);

    m_RigidBody = new RigidBody();

    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 1, 6, 120);
}

void Enemy::Draw()
{
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height, 0);
}

void Enemy::Update(float dt)
{
    m_Animation->SetProps("enemy_idle", 1, 6, 120);

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
    m_Animation->Update();
}

void Enemy::Clean()
{
    TextureManager::GetInstance()->Drop(m_TextureID);
}