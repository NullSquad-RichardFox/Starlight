#pragma once

#include "Starlight/Base.h"
#include "SlateGeometry.h"


class Slate
{
public:
	Slate();

	virtual void OnUpdate(float deltaTime);
	virtual void Draw(SlateGeometry& boxGeometry, SlateGeometry& textGeometry);

	Slate* AddChild(Slate* slate);
	void RemoveFromParent();

	inline uint32 GetChildrenCount() const { return Children.size(); }

	Slate* SetIsStatic(bool bIsStatic);

	inline FUUID GetSlateID() const { return SlateID; }
	inline bool GetIsStatic() const { return bStatic; }

protected:
	bool bStatic;

private:
	void RemoveChild(FUUID slateID);
	void SetParent(Slate* parent);

	FUUID SlateID;
	std::unordered_map<FUUID, std::shared_ptr<Slate>> Children;
	Slate* Parent;

	std::vector<FUUID> RemovedChildren;
};

template<typename T>
static T* NewSlate() 
{ 
	static_assert(std::is_base_of_v<Slate, T>);
	
	return new T();
}