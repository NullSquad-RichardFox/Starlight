#include "Fighter.h"


Fighter::Fighter()
{
	MoveSpeed = 500.0f;

	InputSubsystem::BindKey(EKeyType::W, std::bind(&Fighter::MoveUp, this), EInputAction::Pressed);
	InputSubsystem::BindKey(EKeyType::S, std::bind(&Fighter::MoveDown, this), EInputAction::Pressed);
	InputSubsystem::BindKey(EKeyType::A, std::bind(&Fighter::MoveLeft, this), EInputAction::Pressed);
	InputSubsystem::BindKey(EKeyType::D, std::bind(&Fighter::MoveRight, this), EInputAction::Pressed);
	InputSubsystem::BindKey(EKeyType::Space, std::bind(&Fighter::Shoot, this), EInputAction::Pressed);

	FighterSlate = std::make_shared<Slate>();
	FighterSlate->SetPosition(860, 440);
	FighterSlate->SetSize(200, 200);
	FighterSlate->SetTexture("Assets/Images/fighter.png");
}

void Fighter::MoveUp()
{
	glm::vec2 pos = FighterSlate->GetPosition();
	pos.y += MoveSpeed * Time::GetDeltaTime();
	FighterSlate->SetPosition(glm::clamp(pos, glm::vec2(100), glm::vec2(1820, 980) - FighterSlate->GetSize()));
}

void Fighter::MoveDown()
{
	glm::vec2 pos = FighterSlate->GetPosition();
	pos.y -= MoveSpeed * Time::GetDeltaTime();
	FighterSlate->SetPosition(glm::clamp(pos, glm::vec2(100), glm::vec2(1820, 980) - FighterSlate->GetSize()));
}

void Fighter::MoveLeft()
{
	glm::vec2 pos = FighterSlate->GetPosition();
	pos.x -= MoveSpeed * Time::GetDeltaTime();
	FighterSlate->SetPosition(glm::clamp(pos, glm::vec2(100), glm::vec2(1820, 980) - FighterSlate->GetSize()));
}

void Fighter::MoveRight()
{
	glm::vec2 pos = FighterSlate->GetPosition();
	pos.x += MoveSpeed * Time::GetDeltaTime();
	FighterSlate->SetPosition(glm::clamp(pos, glm::vec2(100), glm::vec2(1820, 980) - FighterSlate->GetSize()));
}

void Fighter::Shoot()
{

}
