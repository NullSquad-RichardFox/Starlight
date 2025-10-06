#include "SlateGeometry.h"
#include "Starlight/Render/VertexArray.h"


SlateGeometry::SlateGeometry()
{
	MaxTexureCount = 0;
	DefaultLayout = nullptr;
}

SlateGeometry::SlateGeometry(uint32 maxTextureCount, const std::shared_ptr<BufferLayout>& layout)
{
	MaxTexureCount = maxTextureCount;
	DefaultLayout = layout;
	CurrentTextureCount = 0;
}

void SlateGeometry::AppendGeometry(const std::vector<float>& vertexData, const std::shared_ptr<Texture>& texture, FUUID slateID, bool bStatic, uint32 slateFlags)
{
	ASSERT(DefaultLayout && MaxTexureCount, "Slate geometry was constructed incorectly, do not use default constructor!");

	// First draw call
	if (SlateGeomertyRegistry.find(slateID) == SlateGeomertyRegistry.end())
	{
		if (!vertexData.size()) return;

		ASSERT(vertexData.size() % DefaultLayout->GetSize() == 0, "Vertex data does not match the buffer layout!");

		uint32 offset = VertexData.size();
		VertexData.reserve(offset + vertexData.size());
		VertexData.insert(VertexData.end(), vertexData.begin(), vertexData.end());

		if (texture)
		{
			Textures.push_back(texture);
			uint32 bufferSize = DefaultLayout->GetSize();
			uint32 vCount = vertexData.size() / bufferSize;
			for (uint32 i = 0; i < vCount; i++)
			{
				if (VertexData[offset + bufferSize * i + 9] == 1.0f)
				{
					VertexData[offset + bufferSize * i + 9] = CurrentTextureCount;
				}
			}

			CurrentTextureCount++;
			if (CurrentTextureCount == MaxTexureCount)
			{
				FlushPoints.push_back(offset);
				CurrentTextureCount = 0;
			}
		}

		SlateGeomertyRegistry[slateID] = offset;
		return;
	}

	// Subsequent draw calls
	
	// Static slates cannot change form, so we use old data
	if (bStatic) return;

	for (uint32 i = 0; i < vertexData.size(); i++)
	{
		// Skip texture ID
		if (i % 10 == 9) continue;

		if (VertexData[SlateGeomertyRegistry[slateID] + i] == vertexData[i])
			continue;

		VertexData[SlateGeomertyRegistry[slateID] + i] = vertexData[i];
	}
}

void SlateGeometry::Clear()
{
	VertexData.clear();
	Textures.clear();
	FlushPoints.clear();
	CurrentTextureCount = 0;
}