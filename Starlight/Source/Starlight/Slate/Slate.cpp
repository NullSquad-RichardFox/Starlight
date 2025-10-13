#include "Slate.h"


Slate::Slate()
{
	SlateID = FUUID();
	bStatic = false;
}

Slate::~Slate()
{
}

Slate* Slate::AddChild(Slate* slate)
{
	std::shared_ptr<Slate> s(slate);
	s->SetParent(this);
	Children[s->GetSlateID()] = s;
	return this;
}

void Slate::RemoveChild(FUUID slateID)
{
	Children.erase(slateID);
	RemovedChildren.push_back(slateID);
}

void Slate::RemoveFromParent()
{
	if (Parent)
	{
		Parent->RemoveChild(SlateID);
	}
}

Slate* Slate::SetIsStatic(bool bIsStatic)
{
	bStatic = bIsStatic;
	return this;
}

void Slate::SetParent(Slate* parent)
{
	Parent = parent;
}

void Slate::OnUpdate(float deltaTime)
{
	for (const auto& [id, slate] : Children)
		slate->OnUpdate(deltaTime);
}

void Slate::Draw(SlateGeometry& boxGeometry, SlateGeometry& textGeometry)
{
	for (const FUUID& id : RemovedChildren)
	{
		boxGeometry.EraseGeometry(id);
		textGeometry.EraseGeometry(id);
	}

	RemovedChildren.clear();

	for (const auto& [id, slate] : Children)
		slate->Draw(boxGeometry, textGeometry);
}