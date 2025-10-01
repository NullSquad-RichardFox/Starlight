#include "Shader.h"

#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"


Shader::Shader(const std::filesystem::path& shaderPath)
{
	std::string src = ReadFile(shaderPath);
	std::unordered_map<GLuint, std::string> shaderData = ParseShader(src);

	CreateProgram(shaderData[GL_VERTEX_SHADER].c_str(), shaderData[GL_FRAGMENT_SHADER].c_str());
}

Shader::Shader(const std::string& shaderSrc)
{
	std::unordered_map<GLuint, std::string> shaderData = ParseShader(shaderSrc);

	CreateProgram(shaderData[GL_VERTEX_SHADER].c_str(), shaderData[GL_FRAGMENT_SHADER].c_str());
}

Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
{
	CreateProgram(vertexSrc.c_str(), fragmentSrc.c_str());
}

Shader::~Shader()
{
	glDeleteProgram(ShaderID);
}

std::string Shader::ReadFile(const std::filesystem::path& path)
{
	std::ifstream file(path, std::ios::in);
	//LOG("Path: {0}", path);
	ASSERT(file, "Couldn't open shader file!");
	if (!file) return "";

	file.seekg(0, std::ios::end); // sets the last line as the current line
	size_t length = file.tellg(); // tells the line pos

	ASSERT(length != -1, "Couldn't open shader file!");
	if (length == -1) return "";

	std::string src;
	src.resize(length);
	file.seekg(0, std::ios::beg); // resets
	file.read(&src[0], length); // coppies the data

	return src;
}

std::unordered_map<GLuint, std::string> Shader::ParseShader(const std::string& file)
{
	std::string typeToken = "#type ";
	size_t typePos = file.find(typeToken, 0);

	std::unordered_map<GLuint, std::string> shaderData;

	ASSERT(typePos != std::string::npos, "Syntax error: shader type not specified!");
	while (typePos != std::string::npos)
	{
		size_t typePosEnd = file.find_first_of('\n', typePos);
		std::string typeSrc = file.substr(typePos + typeToken.size(), typePosEnd - typeToken.size() - typePos);

		GLenum type;
		if (typeSrc == "vertex")
		{
			type = GL_VERTEX_SHADER;
		}
		else if (typeSrc == "fragment")
		{
			type = GL_FRAGMENT_SHADER;
		}
		else
		{
			ASSERT(false, "Syntax error: wrong shader type!");
			return {};
		}

		size_t shaderSrcStart = file.find_first_not_of('\n', typePosEnd);
		ASSERT(shaderSrcStart != std::string::npos, "Syntax error: shader code missing!");
		if (shaderSrcStart == std::string::npos) return {};

		typePos = file.find(typeToken, shaderSrcStart);
		shaderData[type] = typePos == std::string::npos ? file.substr(shaderSrcStart) : file.substr(shaderSrcStart, typePos - shaderSrcStart);
	}

	ASSERT(shaderData.size() == 2, "IShader file doesn't contain both shade types!");
	if (shaderData.size() != 2) return {};

	return shaderData;
}

void Shader::CreateProgram(const char* vertexSrc, const char* fragmentSrc)
{
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	const GLchar* source = vertexSrc;
	glShaderSource(vertexShader, 1, &source, 0);

	glCompileShader(vertexShader);

	GLint isCompiled = 0;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLenght = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLenght);

		std::vector<GLchar> infoLog(maxLenght);
		glGetShaderInfoLog(vertexShader, maxLenght, &maxLenght, &infoLog[0]);

		glDeleteShader(vertexShader);

		LOG_ERROR("{0}", (char*)infoLog.data());
		ASSERT(false, "Vertex shader did not compile!");

		return;
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	source = (const GLchar*)fragmentSrc;
	glShaderSource(fragmentShader, 1, &source, 0);

	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLenght = 0;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLenght);

		std::vector<GLchar> infoLog(maxLenght);
		glGetShaderInfoLog(fragmentShader, maxLenght, &maxLenght, &infoLog[0]);

		glDeleteShader(fragmentShader);
		glDeleteShader(vertexShader);

		LOG_ERROR("{0}", (char*)infoLog.data());
		ASSERT(false, "Fragment shader did not compile!");

		return;
	}

	ShaderID = glCreateProgram();

	glAttachShader(ShaderID, vertexShader);
	glAttachShader(ShaderID, fragmentShader);

	glLinkProgram(ShaderID);

	GLint isLinked = 0;
	glGetProgramiv(ShaderID, GL_LINK_STATUS, (int32*)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLenght = 0;
		glGetProgramiv(ShaderID, GL_INFO_LOG_LENGTH, &maxLenght);

		std::vector<GLchar> infoLog(maxLenght);
		glGetProgramInfoLog(ShaderID, maxLenght, &maxLenght, &infoLog[0]);

		glDeleteProgram(ShaderID);

		glDeleteShader(fragmentShader);
		glDeleteShader(vertexShader);

		LOG_ERROR("{0}", (char*)infoLog.data());
		ASSERT(false, "IShader m_ShaderID did not compile!");

		return;
	}

	glDetachShader(ShaderID, vertexShader);
	glDetachShader(ShaderID, fragmentShader);
}

void Shader::Bind() const
{
	glUseProgram(ShaderID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::SetBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ShaderID, name.c_str()), (int32)value);
}

void Shader::SetInt(const std::string& name, int32 value) const
{
	glUniform1i(glGetUniformLocation(ShaderID, name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ShaderID, name.c_str()), value);
}

void Shader::SetMat4(const std::string& name, const glm::mat4& matrix) const
{
	GLuint loc = glGetUniformLocation(ShaderID, name.c_str());
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::SetFloat3(const std::string& name, glm::vec3 value) const
{
	GLuint loc = glGetUniformLocation(ShaderID, name.c_str());
	glUniform3f(loc, value.x, value.y, value.z);
}

void Shader::SetFloat4(const std::string& name, glm::vec4 value) const
{
	GLuint loc = glGetUniformLocation(ShaderID, name.c_str());
	glUniform4f(loc, value.x, value.y, value.z, value.w);
}