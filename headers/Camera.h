#pragma once
#include <Types.h>

class Camera
{
private:
	vec3 position;
	vec3 lookAt;

	float fov;
	
	vec3 forward;
	vec3 up;

public:

	mat4 transformation;

public:

	Camera(vec3 pos, vec3 lookAt);
	~Camera();

	void moveForward(f32 value);
	void moveRight(f32 value);
	void moveUp(f32 value);

	void updateTransformation();
	mat4 getTransformation() const;
};

