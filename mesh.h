#pragma once

#ifndef MESH_H
#define MESH_H

#include"obj_loader.h"

#include<glm/glm.hpp>
#include<GL/glew.h>

class Vertex
{
public:
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal = glm::vec3(0, 0, 0)) { this->pos = pos; this->texCoord = texCoord; this->normal = normal; }

	inline glm::vec3* GetPos() { return &pos; }
	inline glm::vec2* GetTexCoord() { return &texCoord; }
	inline glm::vec3* GetNormal() { return &normal; }

	inline void SetPos(glm::vec3 Apos) { pos = Apos; }
	inline void SetTexCoord(glm::vec2 tex) { texCoord = tex; }
	inline void SetNormal(glm::vec3 nor) { normal = nor; }

protected:
private:
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
};

class Mesh
{
public:
	Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	Mesh(const std::string& fileName);

	void Draw();

	virtual ~Mesh();
protected:
private:
	Mesh(const Mesh& other) {}
	Mesh& operator=(const Mesh& other) {}

	void InitMesh(const IndexedModel& model);

	enum
	{
		POSITION_VB,
		TEXCOORD_VB,
		NORMAL_VB,

		INDEX_VB,

		NUM_BUFFERS
	};

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;
};

#endif

