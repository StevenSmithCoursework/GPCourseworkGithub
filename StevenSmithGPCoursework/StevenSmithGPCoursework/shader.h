#pragma once

#include "transform.h"
#include "camera.h"
#include <string>
#include <GL/glew.h>
#include <iostream>
#include <fstream>

class Shader
{
public:
	Shader(const std::string& fileName);

	void BindShader();
	void Update(const Transform& transform, const Camera& camera);

	~Shader();

private:
	static const unsigned int NUM_SHADER = 2;

	enum
	{
		TRANSFORM_U,
		NUM_UNIFORMS
	};

	GLuint m_program;
	GLuint m_shaders[NUM_SHADER];
	GLuint m_uniforms[NUM_UNIFORMS];
};

