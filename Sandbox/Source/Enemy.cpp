#include "Enemy.h"


EnemyShip::EnemyShip()
{
    Position = glm::vec2((float)std::rand() / (float)RAND_MAX * 1920.f, 1040.f);
    Size = glm::vec2(40.f);
    SlateTexture = std::make_shared<Texture>("Assets/Images/enemy.png");
}

void EnemyShip::OnUpdate(float deltaTime)
{
    BoxSlate::OnUpdate(deltaTime);

    float dispY = (float)std::rand() / (float)RAND_MAX * 2 - 1;
    Position.y -= dispY <= 0 ? 0 : dispY * deltaTime; 

    float moveSpeed = 10.f;
    float dispX = (float)std::rand() / (float)RAND_MAX * moveSpeed - moveSpeed / 2.f;
    Position.x += dispX;
}