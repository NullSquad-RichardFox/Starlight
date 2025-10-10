#include "Fighter.h"
#include "Bullet.h"


Fighter::Fighter()
{
	MoveSpeed = 500.0f;
	FireDelay = 0.1f;
	CurrentFireDelay = 0;

	InputSubsystem::BindKey(EKeyType::W, std::bind(&Fighter::MoveUp, this), EInputAction::Pressed);
	InputSubsystem::BindKey(EKeyType::S, std::bind(&Fighter::MoveDown, this), EInputAction::Pressed);
	InputSubsystem::BindKey(EKeyType::A, std::bind(&Fighter::MoveLeft, this), EInputAction::Pressed);
	InputSubsystem::BindKey(EKeyType::D, std::bind(&Fighter::MoveRight, this), EInputAction::Pressed);
	InputSubsystem::BindKey(EKeyType::Space, std::bind(&Fighter::Shoot, this), EInputAction::Pressed);

	Position = glm::vec2(860, 440);
	Size = glm::vec2(200, 200);
	SlateTexture = std::make_shared<Texture>("Assets/Images/fighter.png");

	ChildCounter = NewSlate<TextSlate>()->SetPosition(1750, 1040);
	AddChild(ChildCounter);
}

void Fighter::OnUpdate(float deltaTime)
{
	Slate::OnUpdate(deltaTime);

	ChildCounter->SetText("Children: " + std::to_string(GetChildrenCount() - 1));

	if (CurrentFireDelay > 0) 
		CurrentFireDelay -= deltaTime;
}

void Fighter::MoveUp()
{
	glm::vec2 pos = Position;
	pos.y += MoveSpeed * Time::GetDeltaTime();
	Position = glm::clamp(pos, glm::vec2(100), glm::vec2(1820, 980) - Size);
}

void Fighter::MoveDown()
{
	glm::vec2 pos = Position;
	pos.y -= MoveSpeed * Time::GetDeltaTime();
	Position = glm::clamp(pos, glm::vec2(100), glm::vec2(1820, 980) - Size);
}

void Fighter::MoveLeft()
{
	glm::vec2 pos = Position;
	pos.x -= MoveSpeed * Time::GetDeltaTime();
	Position = glm::clamp(pos, glm::vec2(100), glm::vec2(1820, 980) - Size);
}

void Fighter::MoveRight()
{
	glm::vec2 pos = Position;
	pos.x += MoveSpeed * Time::GetDeltaTime();
	Position = glm::clamp(pos, glm::vec2(100), glm::vec2(1820, 980) - Size);
}

void Fighter::Shoot()
{
	if (CurrentFireDelay <= 0)
	{
		AddChild(NewSlate<Bullet>()->SetPosition(Position + Size / 2.f));
		CurrentFireDelay = FireDelay;
	}
}
