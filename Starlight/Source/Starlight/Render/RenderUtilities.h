#pragma once

#include "Starlight/Base.h"


class VertexArray;

class RenderUtilities
{
public:
	static void Initialize();
	static void Shutdown();
	static void Clear();
	static void SetClearColor(glm::vec4 inColor);
	static void DrawElements(const std::shared_ptr<VertexArray>& vertexArray);
	static void SetViewport(int32 width, int32 height);
	static void RenderWireframeOn();
	static void RenderWireframeOff();
};