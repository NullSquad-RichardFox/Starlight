#pragma once

#include "Starlight/Base.h"


class Texture;

class Font
{
public:
	Font(const std::filesystem::path& path);

	void GetCharTextCoords(char c, glm::vec2& outTextCoordMin, glm::vec2& outTextCoordMax) const;
	void GetCharSize(char c, float scale, glm::vec2& outSizeMin, glm::vec2& outSizeMax) const;
	float GetAdvance(char char1, char char2, float scale) const;

	inline float GetAscenderY() const { return AscenderY; }
	inline float GetDescenderY() const { return DescenderY; }
	inline float GetLineHeight() const { return LineHeight; }

	const std::shared_ptr<Texture>& GetTexture() const { return FontTexture; }

private:
	std::shared_ptr<Texture> FontTexture;
	std::map<std::pair<int, int>, double> Kerning;
	std::map<char, glm::vec4> CharTextCoords;
	std::map<char, glm::vec4> CharSizes;
	std::map<char, float> CharAdvance;

	float LineHeight;
	float DescenderY;
	float AscenderY;
};