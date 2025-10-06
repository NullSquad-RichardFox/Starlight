#pragma once

#include "Starlight/Base.h"
#include "Slate.h"


class ButtonSlate : public Slate
{
public:
	ButtonSlate();

	void BindOnClicked(const std::function<void()>& callback);
	void BindOnHovered(const std::function<void()>& callback);
	void BindOnUnhovered(const std::function<void()>& callback);

protected:
	virtual void OnClicked();
	virtual void OnHovered();
	virtual void OnUnhovered();

private:
	void LeftMouseClick();
	void MouseMove(glm::vec2 dir);

	std::vector<std::function<void()>> ButtonClickedCallback;
	std::vector<std::function<void()>> ButtonHoveredCallback;
	std::vector<std::function<void()>> ButtonUnhoveredCallback;
};