#include "SlateGeometry.h"
#include "Starlight/Render/VertexArray.h"


SlateGeometry::SlateGeometry()
{
	MaxTextureCount = 0;
	BufferSize = 0;
}

SlateGeometry::SlateGeometry(uint32 maxTextureCount, uint32 bufferSize)
{
	MaxTextureCount = maxTextureCount;
	BufferSize = bufferSize;
}

void SlateGeometry::AppendGeometry(FUUID slateID, const std::vector<float>& data, const std::shared_ptr<Texture>& texture, uint32 slateFlags)
{
	if (!data.size()) return;

	ASSERT(data.size() % BufferSize == 0, "Data provided is outside standard range!");

	// Slate already loaded in memory
	if (auto it = SlateIndexRegistry.find(slateID); it != SlateIndexRegistry.end())
	{
		if (data.size() > CellSizes[it->second])
		{
			EraseGeometry(slateID);
			AppendGeometry(slateID, data, texture, slateFlags);
		}

		// Static data does not change
		if ((slateFlags & SF_Static) == SF_Static) return;

		for (uint32 i = 0; i < CellSizes[it->second]; i++)
		{
			if (i % BufferSize == 9) continue;

			VertexDataCache[it->second + i] = data[i];
		}

		return;
	}

	// Append to the end if no space is free
	SlateIndexRegistry[slateID] = VertexDataCache.size();
	CellSizes[VertexDataCache.size()] = data.size();
	
	if (texture)
	{
		if (auto it = std::find(TextureStorage.begin(), TextureStorage.end(), texture); it != TextureStorage.end())
		{
			TextureRegistry.insert({ VertexDataCache.size(), it - TextureStorage.begin()});
		}
		else
		{
			TextureRegistry.insert({ VertexDataCache.size(), TextureStorage.size()});
			TextureStorage.push_back(texture);
		}
	}
	VertexDataCache.insert(VertexDataCache.end(), data.begin(), data.end());
	RecacheFlushData();
}

// Can be slower
void SlateGeometry::EraseGeometry(FUUID slateID)
{
	if (auto it = SlateIndexRegistry.find(slateID); it != SlateIndexRegistry.end())
	{
		// Remove textures
		if (auto tIt = TextureRegistry.find(it->second); tIt != TextureRegistry.end())
		{
			uint32 textureID = tIt->second;
			TextureRegistry.erase(tIt);
			bool bNoneRemaining = true;
			for (const auto& [id, texID] : TextureRegistry)
			{
				if (texID == textureID)
				{
					bNoneRemaining = false;
					break;
				}
			}

			if (bNoneRemaining)
			{
				TextureStorage.erase(TextureStorage.begin() + textureID);
				for (auto& [id, texID] : TextureRegistry)
				{
					if (texID > textureID)
					{
						texID--;
					}
				}
			}
		}

		// Resets values in cache
		VertexDataCache.erase(VertexDataCache.begin() + it->second, VertexDataCache.begin() + it->second + CellSizes[it->second]);
		for (auto& [slate, index] : SlateIndexRegistry)
		{
			if (index > it->second) index -= CellSizes[it->second];
		}

		std::map<uint32, uint32> newTextRegistry;
		for (auto& [index, texID] : TextureRegistry)
		{
			if (index == it->second) continue;

			newTextRegistry.insert({ index > it->second ? index - CellSizes[it->second] : index, texID });
		}

		std::unordered_map<uint32, uint32> newCells;
		for (auto& [index, size] : CellSizes)
		{
			if (index == it->second) continue;

			newCells[index > it->second ? index - CellSizes[it->second] : index] = size;
		}

		TextureRegistry = newTextRegistry;
		CellSizes = newCells;
		SlateIndexRegistry.erase(it);

		RecacheFlushData();
	}
}

// Needs to be fast
void SlateGeometry::GetFlushData(std::vector<std::pair<void*, uint32>>& vData, std::vector<std::shared_ptr<Texture>>& textures) const
{
	vData = CachedFlushData;
	textures = TextureStorage;
}

void SlateGeometry::RecacheFlushData()
{
	CachedFlushData.clear();
	CachedFlushData.reserve(TextureStorage.size() / MaxTextureCount + 1);
	
	uint32 prevIndex = 0; 
	
	// Itter through all data
	for (const auto& [index, size] : CellSizes)
	{
		// Handle texture
		if (auto it = TextureRegistry.find(index); it != TextureRegistry.end())
		{
			for (uint32 i = 0; i < (size / BufferSize); i++)
				VertexDataCache[index + BufferSize * i + 9] = it->second % MaxTextureCount;
	
			if (it->second % MaxTextureCount == MaxTextureCount - 1)
			{
				CachedFlushData.push_back(std::make_pair<void*, uint32>(VertexDataCache.data() + prevIndex, index - prevIndex));
				prevIndex = index;
			}
		}
	}

	CachedFlushData.push_back(std::make_pair<void*, uint32>(VertexDataCache.data() + prevIndex, VertexDataCache.size() - prevIndex));
}