#include "shader.h"

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);

static GLuint CreateShader(const std::string& text, GLenum shaderType);

Shader::Shader(const std::string& filename)
{
	m_program = glCreateProgram();
	m_shaders[0] = CreateShader(LoadShader(filename + ".vs.txt"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(filename + ".fs.txt"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
		glAttachShader(m_program, m_shaders[i]);//Adding each shader to the program.

	glBindAttribLocation(m_program, 0, "position");
	glBindAttribLocation(m_program, 1, "texCoord");
	glBindAttribLocation(m_program, 2, "normal");

	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "[Error]: program failed to link!: ");
	
	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "[Error]: program is invalid!: ");

	m_uniforms[MODEL_U] = glGetUniformLocation(m_program, "model");
	m_uniforms[VIEWANDPROJECTION_U] = glGetUniformLocation(m_program, "viewAndProjection");
	m_uniforms[VIEW_U] = glGetUniformLocation(m_program, "viewMat");
	m_uniforms[PROJECTION_U] = glGetUniformLocation(m_program, "projectionMat");
	m_uniforms[NORMALMAT_U] = glGetUniformLocation(m_program, "normalMatrix");
	m_uniforms[LIGHTVEC_U] = glGetUniformLocation(m_program, "lightVec");
	m_uniforms[SKYCOLOUR_U] = glGetUniformLocation(m_program, "skyColour");
}

Shader::~Shader()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}

	glDeleteProgram(m_program);
}
static GLuint CreateShader(const std::string& text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0)
		std::cerr << "[Error]: shader creation failed!:" << std::endl;

	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];

	shaderSourceStrings[0] = text.c_str();
	shaderSourceStringLengths[0] = text.length();

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "[Error]: shader compilation failed!: ");

	return shader;
}

std::string Shader::LoadShader(const std::string& fileName)
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
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}

void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}

void Shader::Bind()
{
	glUseProgram(m_program);
}

void Shader::Update(const Transform& transform, const Camera& camera, const glm::vec3& light, const glm::vec3& sky)
{
	glm::mat4 model = transform.GetModel();
	glm::mat4 viewAndProjection = camera.GetViewProjection();
	glm::mat4 viewMat = camera.GetView();
	glm::mat4 projectionMat = camera.GetProjection();
	glm::mat3 normalMatrix = glm::mat3(glm::transpose(glm::inverse(model)));
	glm::vec3 lightVec = light;	
	glm::vec3 skyColour = sky;

	glUniformMatrix4fv(m_uniforms[MODEL_U], 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(m_uniforms[VIEWANDPROJECTION_U], 1, GL_FALSE, &viewAndProjection[0][0]);
	glUniformMatrix4fv(m_uniforms[VIEW_U], 1, GL_FALSE, &viewMat[0][0]);
	glUniformMatrix4fv(m_uniforms[PROJECTION_U], 1, GL_FALSE, &projectionMat[0][0]);
	glUniformMatrix3fv(m_uniforms[NORMALMAT_U], 1, GL_FALSE, &normalMatrix[0][0]);
	glUniform3fv(m_uniforms[LIGHTVEC_U], 1, &lightVec[0]);
	glUniform3fv(m_uniforms[SKYCOLOUR_U], 1, &skyColour[0]);
}
