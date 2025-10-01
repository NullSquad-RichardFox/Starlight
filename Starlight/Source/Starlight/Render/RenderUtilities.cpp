#include "RenderUtilities.h"
#include "VertexArray.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"


void RenderUtilities::Initialize()
{
	glfwInit();
}

void RenderUtilities::Shutdown()
{
	glfwTerminate();
}

void RenderUtilities::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderUtilities::SetClearColor(glm::vec4 inColor)
{
	glClearColor(inColor.x, inColor.y, inColor.z, inColor.w);
}

void RenderUtilities::DrawElements(const std::shared_ptr<VertexArray>& vertexArray)
{
	glDrawElements(GL_TRIANGLES, vertexArray->GetIndexCount(), GL_UNSIGNED_INT, 0);
}

void RenderUtilities::SetViewport(int32 width, int32 height)
{
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

void RenderUtilities::RenderWireframeOn()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDisable(GL_CULL_FACE);
}

void RenderUtilities::RenderWireframeOff()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_CULL_FACE);
}
