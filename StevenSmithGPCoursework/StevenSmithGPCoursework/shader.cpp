#include "shader.h"

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static std::string LoadShader(const std::string& fileName);
static GLuint CreateShader(const std::string& text, GLenum shaderType);

Shader::Shader(const std::string& fileName)
{
	//Creates the program by allocating space for it
	m_program = glCreateProgram();
	//Finds and creates the shaders from the folders position
	m_shaders[0] = CreateShader(LoadShader(fileName + ".vvs"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(fileName + ".ffs"), GL_FRAGMENT_SHADER);

	//Attaches the shaders to the program
	for (unsigned int i = 0; i < NUM_SHADER; i++)
	{
		glAttachShader(m_program, m_shaders[i]);
	}

	//Tells the shader where it's mapping the attribute
	glBindAttribLocation(m_program, 0, "position");
	glBindAttribLocation(m_program, 1, "texCoord");
	glBindAttribLocation(m_program, 2, "normal");
	
	//Check for errors in the program
	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Shader failed to link: ");

	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Shader unvalidated: ");

	//Updates the location of the attributes
	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");
}


Shader::~Shader()
{
	//Detaches the shaders from the shader program and deletes them
	for (unsigned int i = 0; i < NUM_SHADER; i++)
	{
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}
	//Deletes the overall shader program
	glDeleteProgram(m_program);
}

//Binds any shaders created to the program
void Shader::BindShader()
{
	glUseProgram(m_program);
}

//Used to update the transforms of the models in relation to the camera
void Shader::Update(const Transform& transform, const Camera& camera)
{
	glm::mat4 model = camera.GetViewProjection() * transform.GetModel();

	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
}

static GLuint CreateShader(const std::string& text, GLenum shaderType)
{
	//Creates the shader
	GLuint shader = glCreateShader(shaderType);

	//Checks the shader exists
	if (shader == 0)
	{
		std::cerr << "Error:Shader creation failed" << std::endl;
	}

	//Creates a list of strings from the shader and saves the length of the string
	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];

	//Translate the previous strings into C language and takes in the length 
	shaderSourceStrings[0] = text.c_str();
	shaderSourceStringLengths[0] = text.length();

	//Sends the shader code to OpenGL and compiles it
	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader(shader);

	//Checks for any errors in the compilation of the shader
	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error:Shader could not compile");

	//return the created shader
	return shader;
}

//Loads the shader from a file
static std::string LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load the shader correctly: " << fileName << std::endl;
	}
	return output;
}

//Check for errors in the shader
static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
	{
		glGetProgramiv(shader, flag, &success);
	}
	else
	{
		glGetShaderiv(shader, flag, &success);
	}

	if (success == GL_FALSE)
	{
		if (isProgram)
		{
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		}
		else
		{
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		}

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}
