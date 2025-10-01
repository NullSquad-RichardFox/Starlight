#include "Camera.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/quaternion.hpp"


Camera::Camera(float aspectRatio, float zoomLevel)
	:AspectRatio(aspectRatio), ZoomLevel(zoomLevel), Rotation(0.0f), Position(0.0f), ProjMat(1.0f), ViewMat(1.0f), ViewProjMat(1.0f)
{
	RecalculateCameraMatrices();
}

Camera::~Camera()
{
}

void Camera::OnUpdate(float deltaTime)
{
	if (bUpdateMatrices) RecalculateCameraMatrices();
}

void Camera::SetZoomLevel(float zoomLevel)
{
	ZoomLevel = zoomLevel;
	bUpdateMatrices = true;
}

void Camera::SetAspectRatio(float aspectRatio)
{
	AspectRatio = aspectRatio;
	bUpdateMatrices = true;
}

void Camera::SetPosition(glm::vec3 position)
{
	Position = position;
	bUpdateMatrices = true;
}

void Camera::SetRotation(glm::vec3 rotation)
{
	Rotation = rotation;
	bUpdateMatrices = true;
}

void Camera::RecalculateCameraMatrices()
{
	ProjMat = glm::ortho<float>(-AspectRatio * ZoomLevel, AspectRatio * ZoomLevel, -ZoomLevel, ZoomLevel, -1, 1);

	glm::quat q(Rotation);
	ViewMat = glm::inverse(glm::translate(glm::mat4(1.0f), Position) * glm::toMat4(q));

	ViewProjMat = ViewMat * ProjMat;
	bUpdateMatrices = false;
}
