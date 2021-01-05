#include<Windows.h>
#include<gl/GLU.h>
#include "Camera.h"


Camera::Camera(vec3 pos)
{
	m_pos = vec3(pos);
	m_dir = vec3(0.0, 0.0, -1.0);
	m_left = vec3(-1.0, 0.0, 0.0);
	m_up = vec3(0.0, 1.0, 0.0);
	m_veloc = vec3(0.0, 0.0, 0.0);
}


Camera::~Camera()
{
}

void Camera::ativar()
{
	vec3 look = m_pos + m_dir;
	gluLookAt(m_pos.x, m_pos.y, m_pos.z, look.x, look.y, look.z, m_up.x, m_up.y, m_up.z);
}

void Camera::forward()
{
	m_veloc = m_dir * m_scl;
	m_pos = m_pos + m_veloc;
}

void Camera::back()
{
	m_veloc = m_dir * (-m_scl);
	m_pos = m_pos + m_veloc;
}

void Camera::left()
{
	m_veloc = m_left * m_scl;
	m_pos = m_pos + m_veloc;
}

void Camera::right()
{
	m_veloc = m_left * (-m_scl);
	m_pos = m_pos + m_veloc;
}

void Camera::updateYaw(float dYaw)
{
	if (m_yaw <= 60.0 || m_yaw >= -60.0)
		m_yaw += dYaw;
}

void Camera::update()
{
	float ang = cvtToRad(m_yaw);
	if (m_yaw <= 60.0 || m_yaw >= -60.0)
	{
		m_dir.x = sin(ang);
		m_dir.z = -cos(ang);
		m_dir.normalizar();
		m_left = m_up.prodVetorial(m_dir);
	}
}

float Camera::cvtToRad(float ang)
{
	return (ang*m_PI) / 180.0;
}

