#include "ButtonSlate.h"
#include "Utility/Input.h"


ButtonSlate::ButtonSlate()
{
	InputSubsystem::BindKey(EKeyType::LeftMouseButton, std::bind(&ButtonSlate::LeftMouseClick, this));
	InputSubsystem::BindMouse(std::bind(&ButtonSlate::MouseMove, this, std::placeholders::_1));
}

void ButtonSlate::BindOnClicked(const std::function<void()>& callback)
{
	ButtonClickedCallback.push_back(callback);
}

void ButtonSlate::BindOnHovered(const std::function<void()>& callback)
{
	ButtonHoveredCallback.push_back(callback);
}

void ButtonSlate::BindOnUnhovered(const std::function<void()>& callback)
{
	ButtonUnhoveredCallback.push_back(callback);
}

void ButtonSlate::OnClicked()
{
	for (const auto& callback : ButtonClickedCallback)
		callback();
}

void ButtonSlate::OnHovered()
{
	for (const auto& callback : ButtonHoveredCallback)
		callback();
}

void ButtonSlate::OnUnhovered()
{
	for (const auto& callback : ButtonUnhoveredCallback)
		callback();
}

void ButtonSlate::LeftMouseClick()
{
	auto mouse = InputSubsystem::GetMousePos();
	if (mouse.x >= Position.x && mouse.x <= (Position.x + Size.x) && mouse.y >= Position.y && mouse.y <= (Position.y + Size.y))
	{
		OnClicked();
	}
}

void ButtonSlate::MouseMove(glm::vec2 dir)
{
	auto mouse = InputSubsystem::GetMousePos();
	if (mouse.x >= Position.x && mouse.x <= (Position.x + Size.x) && mouse.y >= Position.y && mouse.y <= (Position.y + Size.y))
	{
		// Mouse currently in bounding box
		if ((mouse.x - dir.x) < Position.x || (mouse.x - dir.x) > (Position.x + Size.x) || (mouse.y - dir.y) < Position.y || (mouse.y - dir.y) > (Position.y + Size.y))
		{
			OnHovered();
		}
	}
	else
	{
		// Mouse currently outside bounding box
		if ((mouse.x - dir.x) >= Position.x && (mouse.x - dir.x) <= (Position.x + Size.x) && (mouse.y - dir.y) >= Position.y && (mouse.y - dir.y) <= (Position.y + Size.y))
		{
			OnUnhovered();
		}
	}
}

