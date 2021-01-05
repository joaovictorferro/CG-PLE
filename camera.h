#pragma once
#include<Windows.h>
#include<gl/GLU.h>
#include "cg.h"

class Camera
{
private:
	vec3 m_pos;
	vec3 m_dir;
	vec3 m_left;
	vec3 m_up;
	vec3 m_veloc;
	float m_scl = 0.25;
	float m_yaw;
	float m_PI = 3.14159265;

public:
	Camera(vec3 pos);
	~Camera();
	void ativar();

	void forward();
	void back();
	void left();
	void right();
	void updateYaw(float dYaw);
	void update();

private:
	float cvtToRad(float ang);
};