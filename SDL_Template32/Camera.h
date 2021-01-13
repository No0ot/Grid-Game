#pragma once

#include "GameObject.h"

class Camera : public GameObject
{
public:
	Camera(glm::vec2);
	~Camera();

	void draw() override;
	void update() override;
	void clean() override;
private:
};

