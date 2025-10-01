#pragma once

#include "Base.h"


class Texture;
class BufferLayout;

class SlateGeometry
{
public:
	SlateGeometry();
	SlateGeometry(uint32 maxTextureCount, const std::shared_ptr<BufferLayout>& layout);

	uint32 AppendGeometry(const std::vector<float>& vertexData, const std::shared_ptr<Texture>& texture, uint32 slateID, bool bStatic = false);
	void Clear();

	const std::vector<float>& GetVertexData() const { return VertexData; }
	const std::vector<std::shared_ptr<Texture>>& GetTextures() const { return Textures; }
	const std::vector<uint32>& GetFlushPoints() const { return FlushPoints; }

private:
	std::vector<float> VertexData;
	std::vector<std::shared_ptr<Texture>> Textures;
	std::vector<uint32> FlushPoints;

	uint32 MaxTexureCount;
	std::shared_ptr<BufferLayout> DefaultLayout;
	uint32 CurrentTextureCount;
};