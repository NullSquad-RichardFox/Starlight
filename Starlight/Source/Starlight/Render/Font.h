#pragma once

#include "Base.h"
#undef INFINITE
#include "msdf-atlas-gen/msdf-atlas-gen.h"


class Texture;

class Font
{
public:
	Font(const std::filesystem::path& path);

	void GetCharTextCoords(char c, glm::vec2& outTextCoordMin, glm::vec2& outTextCoordMax) const;
	void GetCharSize(char c, float scale, glm::vec2& outSizeMin, glm::vec2& outSizeMax) const;

	float GetAdvance(char char1, char char2, float scale) const;
	float GetAscenderY() const;
	float GetDescenderY() const;
	float GetLineHeight() const;

	glm::vec2 GetTextSize(float renderScale, const std::string& text) const;

	const std::shared_ptr<Texture>& GetTexture() const { return FontTexture; }

private:
	std::shared_ptr<Texture> FontTexture;
	std::shared_ptr<msdf_atlas::FontGeometry> FontGeometry;
	std::vector<msdf_atlas::GlyphGeometry> Glyphs;
};