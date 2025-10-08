#pragma once

#include "Starlight/Base.h"


class Texture;

enum ESlateFlags : uint32
{
	SF_None 		= 0b0000000000000000,
	SF_Static 		= 0b0000000000000001
};

class SlateGeometry
{
public:
	SlateGeometry();
	SlateGeometry(uint32 maxTextureCount, uint32 bufferSize);

	// Needs to be as fast as possible
	void AppendGeometry(FUUID slateID, const std::vector<float>& data, const std::shared_ptr<Texture>& texture, uint32 slateFlags = 0);

	// Can be slower
	void EraseGeometry(FUUID slateID);

	// Needs to be fast
	void GetFlushData(std::vector<std::vector<std::pair<void*, uint32>>>& vData, std::vector<std::shared_ptr<Texture>>& textures) const;

private:
	void RecacheFlushData();

	std::vector<float> VertexDataCache;
	std::vector<uint32> FreeSlotIndices;
	std::unordered_map<FUUID, uint32> SlateIndexRegistry;
	std::map<uint32, std::shared_ptr<Texture>> Textures;

	std::vector<std::vector<std::pair<void*, uint32>>> CachedFlushData;

	uint32 MaxTextureCount = 32;
	uint32 BufferSize = 10;
	uint32 CellSize = BufferSize * 4;
};