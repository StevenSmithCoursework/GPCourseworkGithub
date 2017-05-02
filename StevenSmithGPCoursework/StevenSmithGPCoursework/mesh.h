#pragma once

#include <glm\glm.hpp>
#include <GL/glew.h>
#include <string>
#include "obj_loader.h"

class Vert
{
public:
	Vert(const glm::vec3& position, const glm::vec2& texCoord, const glm:: vec3& normal = glm::vec3(0,0,0))
	{
		//Setters
		this->position = position;
		this->texCoord = texCoord;
		this->normal = normal;
	}

	//Getters
	inline glm::vec3* GetPosition() { return &position; }
	inline glm::vec2* GetTexCoord() { return &texCoord; }
	inline glm::vec3* GetNormal() { return &normal; }

protected:

private:
	//Variables to get and set
	glm::vec3 position;
	glm::vec2 texCoord;
	glm::vec3 normal;
};

class Mesh
{
public:
	Mesh(Vert* verts, unsigned int numVerts, unsigned int* indices, unsigned int numIndices);
	Mesh(const std::string& fileName);

	void DrawMesh();

	~Mesh();

private:
	void InitMesh(const IndexedModel& model);

	enum
	{
		POSITION_VB,
		TEXCOORD_VB,
		INDEX_VB,
		NORMAL_VB,
		NUM_BUFFERS
	};

	GLuint m_vertArrayObject;
	GLuint m_vertArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;
};

