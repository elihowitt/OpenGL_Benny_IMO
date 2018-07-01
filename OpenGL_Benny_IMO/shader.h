#pragma once

#ifndef SHADER_H
#define SHADER_H

#include<string>
#include<iostream>
#include<fstream>
#include<GL/glew.h>

class Shader
{
public:
	Shader(const std::string& filename);

	void Bind();
	std::string LoadShader(const std::string& filename);

	virtual ~Shader();
protected:
private:
	static const unsigned int NUM_SHADERS = 2;
	Shader(const Shader& other){}
	Shader& operator=(const Shader& other){}

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
};

#endif

