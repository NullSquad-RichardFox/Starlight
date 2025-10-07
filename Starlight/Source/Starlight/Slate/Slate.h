#pragma once

#include "Starlight/Base.h"
#include "SlateGeometry.h"


class Texture;

class Slate
{
public:
	Slate();

	virtual void OnUpdate(float deltaTime);
	virtual void Draw(SlateGeometry& boxGeometry, SlateGeometry& textGeometry);

	Slate* AddChild(Slate* slate);

	Slate* SetPosition(glm::vec2 position);
	Slate* SetPosition(float x, float y);

	Slate* SetSize(glm::vec2 size);
	Slate* SetSize(float x, float y);

	Slate* SetColor(glm::vec4 color);
	Slate* SetColor(float r, float g, float b, float a = 1.0f);

	Slate* SetTexture(const std::shared_ptr<Texture>& texture);
	Slate* SetTexture(const std::string& textureSrc);

	Slate* SetZOrder(float zOrder);
	Slate* SetIsStatic(bool bIsStatic);

	inline glm::vec2 GetPosition() const { return Position; }
	inline glm::vec2 GetSize() const { return Size; }
	inline glm::vec4 GetColor() const { return Color; }
	inline std::shared_ptr<Texture> GetTexture() const { return SlateTexture; }
	inline float GetZOrder() const { return ZOrder; }
	inline bool GetIsStatic() const { return bStatic; }

protected:
	glm::vec2 Position;
	glm::vec2 Size;
	glm::vec4 Color;
	std::shared_ptr<Texture> SlateTexture;
	float ZOrder;

	uint32 DataOffset;
	uint32 DataSize;
	bool bStatic;
	FUUID SlateID;

private:
	std::vector<std::shared_ptr<Slate>> Children;
};

template<typename T>
static T* NewSlate() 
{ 
	static_assert(std::is_base_of_v<Slate, T>);
	
	return new T();
}