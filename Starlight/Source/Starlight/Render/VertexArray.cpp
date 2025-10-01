#include "VertexArray.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"


uint32 Utils::GetShaderDataTypeSize(EShaderDataType type)
{
	switch (type)
	{
	case EShaderDataType::None:		return 0;
	case EShaderDataType::Float:		return 4;
	case EShaderDataType::Float2:	return 8;
	case EShaderDataType::Float3:	return 12;
	case EShaderDataType::Float4:	return 16;
	case EShaderDataType::Mat3:		return 36;
	case EShaderDataType::Mat4:		return 64;
	case EShaderDataType::int32:		return 4;
	case EShaderDataType::Int2:		return 8;
	case EShaderDataType::Int3:		return 12;
	case EShaderDataType::Int4:		return 16;
	case EShaderDataType::Bool:		return 1;
	}

	ASSERT(false, "Unknown EShaderDataType");
	return 0;
}

uint32 Utils::GetShaderDataTypeComponentCount(EShaderDataType type)
{
	switch (type)
	{
	case EShaderDataType::None:		return 0;
	case EShaderDataType::Float:		return 1;
	case EShaderDataType::Float2:	return 2;
	case EShaderDataType::Float3:	return 3;
	case EShaderDataType::Float4:	return 4;
	case EShaderDataType::Mat3:		return 9;
	case EShaderDataType::Mat4:		return 16;
	case EShaderDataType::int32:		return 1;
	case EShaderDataType::Int2:		return 2;
	case EShaderDataType::Int3:		return 3;
	case EShaderDataType::Int4:		return 4;
	case EShaderDataType::Bool:		return 1;
	}

	ASSERT(false, "Unknown EShaderDataType");
	return 0;
}

GLenum Utils::GetShaderDataTypeToOpenGLBaseType(EShaderDataType type)
{
	switch (type)
	{
	case EShaderDataType::None:		return GL_FALSE;

	case EShaderDataType::Float:
	case EShaderDataType::Float2:
	case EShaderDataType::Float3:
	case EShaderDataType::Float4:
	case EShaderDataType::Mat3:
	case EShaderDataType::Mat4:		return GL_FLOAT;

	case EShaderDataType::int32:
	case EShaderDataType::Int2:
	case EShaderDataType::Int3:
	case EShaderDataType::Int4:      return GL_INT;

	case EShaderDataType::Bool:		return GL_INT;
	}

	ASSERT(false, "Unknown EShaderDataType");
	return 0;
}

VertexArray::VertexArray()
{
	glCreateVertexArrays(1, &ArrayID);
	glCreateBuffers(1, &VertexBufferID);
	glCreateBuffers(1, &IndexBufferID);
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &IndexBufferID);
	glDeleteBuffers(1, &VertexBufferID);
	glDeleteVertexArrays(1, &ArrayID);
}

void VertexArray::AddVertexData(const float* vertexData, uint32 size)
{
	ASSERT(ArrayLayout != nullptr, "Buffer layout not bound!");
	ASSERT(ArrayLayout->GetElements().size(), "Bound buffer layout is empty!");

	ASSERT((size % ArrayLayout->GetSize()) == 0, "Vertex data does not match up to current buffer layout!");
	uint32 vCount = size / ArrayLayout->GetSize();

	ASSERT((vCount % 4) == 0, "Vertex data contains incomplete quads!");
	uint32 qCount = vCount / 4;

	IndexCount = 6 * qCount;
	std::vector<uint32> indices;
	indices.reserve(IndexCount);
	for (uint32 i = 0; i < qCount; i++)
	{
		indices.push_back(0 + 4 * i);
		indices.push_back(1 + 4 * i);
		indices.push_back(2 + 4 * i);
		indices.push_back(2 + 4 * i);
		indices.push_back(3 + 4 * i);
		indices.push_back(0 + 4 * i);
	}

	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), vertexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndexCount * sizeof(uint32), indices.data(), GL_STATIC_DRAW);

	uint32 index = 0;
	for (auto& element : *ArrayLayout)
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(
			index,
			Utils::GetShaderDataTypeComponentCount(element.Type),
			Utils::GetShaderDataTypeToOpenGLBaseType(element.Type),
			element.bNormalized ? GL_TRUE : GL_FALSE,
			ArrayLayout->GetStride(),
			(const void*)element.Offset
		);
		index++;
	}
}

void VertexArray::BindBufferLayout(const std::shared_ptr<BufferLayout>& bufferLayout)
{
	ArrayLayout = bufferLayout;
}
