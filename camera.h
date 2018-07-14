#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include<glm/glm.hpp>
#include<glm/gtx/transform.hpp>

class Camera
{
public:
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
	{
		m_perspective = glm::perspective(fov, aspect, zNear, zFar);
		m_position = pos;
		m_forward = glm::vec3(0, 0, 1);
		m_up = glm::vec3(0, 1, 0);
	}

	inline glm::mat4 GetViewProjection() const
	{
		return m_perspective * glm::lookAt(m_position, m_position + m_forward, m_up);
	}
	inline glm::mat4 GetProjection() const
	{
		return m_perspective;
	}
	inline glm::mat4 GetView() const
	{
		return glm::lookAt(m_position, m_position + m_forward, m_up);
	}

	void Pitch(float Angle)
	{
		m_pitch += Angle;
		if (m_pitch > 89.0f) //Stop the camera from flipping upside down
			m_pitch = 89.0f;
		if (m_pitch < -89.0f)
			m_pitch = -89.0f;
		m_forward = glm::normalize(glm::vec3(
			cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch)),
			sin(glm::radians(m_pitch)),
			sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch)))
		);

			m_up = glm::normalize(glm::cross(glm::cross(m_forward, glm::vec3(0, 1, 0)), m_forward));
	}
	void Yaw(float Angle)
	{
		m_yaw = glm::mod(m_yaw + Angle, 360.0f);
		m_forward = glm::normalize(glm::vec3(
			cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch)),
			sin(glm::radians(m_pitch)),
			sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch)))
		);

		m_up = glm::normalize(glm::cross(glm::cross(m_forward, glm::vec3(0, 1, 0)), m_forward));
	}

	glm::mat4& GetPerspective() { return m_perspective; }
	glm::vec3& GetPosition() { return m_position; }
	glm::vec3& GetForward() { return m_forward; }
	glm::vec3& GetUp() { return m_up; }
protected:
private:
	glm::mat4 m_perspective;
	glm::vec3 m_position;
	glm::vec3 m_forward;
	glm::vec3 m_up;

	float m_pitch, m_yaw;//From discord helping me rotate.
};

#endif