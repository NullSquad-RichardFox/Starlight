#pragma once

#include "Starlight/Base.h"
#include "Starlight/Slate/Slate.h"


class BoxSlate : public Slate
{
public:
	BoxSlate();

	virtual void Draw(SlateGeometry& boxGeometry, SlateGeometry& textGeometry) override;

	BoxSlate* SetPosition(glm::vec2 position);
	BoxSlate* SetPosition(float x, float y);

	BoxSlate* SetSize(glm::vec2 size);
	BoxSlate* SetSize(float x, float y);

	BoxSlate* SetColor(glm::vec4 color);
	BoxSlate* SetColor(float r, float g, float b, float a = 1.0f);

	BoxSlate* SetTexture(const std::shared_ptr<Texture>& texture);
	BoxSlate* SetTexture(const std::string& textureSrc);

	BoxSlate* SetZOrder(float zOrder);

	inline glm::vec2 GetPosition() const { return Position; }
	inline glm::vec2 GetSize() const { return Size; }
	inline glm::vec4 GetColor() const { return Color; }
	inline std::shared_ptr<Texture> GetTexture() const { return SlateTexture; }
	inline float GetZOrder() const { return ZOrder; }

protected:
	glm::vec2 Position;
	glm::vec2 Size;
	glm::vec4 Color;
	std::shared_ptr<Texture> SlateTexture;
	float ZOrder;
};