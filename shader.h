#pragma once

#ifndef SHADER_H
#define SHADER_H

#include<string>
#include<iostream>
#include<fstream>
#include<GL/glew.h>

#include"transform.h"
#include"camera.h"

class Shader
{
public:
	Shader(const std::string& filename);

	void Bind();
	void Update(const Transform& transform, const Camera& cameraconst, const glm::vec3& = glm::vec3(0,0,1), const glm::vec3& = glm::vec3(0.4,0.4,0.4));
	std::string LoadShader(const std::string& filename);///
	
	virtual ~Shader();
protected:
private:
	static const unsigned int NUM_SHADERS = 2;
	Shader(const Shader& other){}
	Shader& operator=(const Shader& other){}

	enum
	{
		MODEL_U,
		VIEWANDPROJECTION_U,
		VIEW_U,
		PROJECTION_U,
		NORMALMAT_U,
		LIGHTVEC_U,
		SKYCOLOUR_U,

		NUM_UNIFORMS
	};

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];
};

#endif
