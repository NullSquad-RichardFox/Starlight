#pragma once

#include "Base.h"


class Camera
{
public:
	Camera(float aspectRatio, float zoomLevel);
	~Camera();

	virtual void OnUpdate(float deltaTime);
	void SetZoomLevel(float zoomLevel);
	void SetAspectRatio(float aspectRatio);
	void SetPosition(glm::vec3 position);
	void SetRotation(glm::vec3 rotation);

	inline const glm::mat4& GetViewProjMat() const { return ViewProjMat; }

private:
	void RecalculateCameraMatrices();

	float ZoomLevel;
	float AspectRatio;

	glm::mat4 ViewMat;
	glm::mat4 ProjMat;
	glm::mat4 ViewProjMat;

	glm::vec3 Rotation;
	glm::vec3 Position;

	bool bUpdateMatrices;
};