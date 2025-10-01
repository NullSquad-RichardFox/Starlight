#pragma once

#include "Base.h"


typedef uint32 GLuint;

class Shader
{
public:
	Shader(const std::filesystem::path& shaderPath);
	explicit Shader(const std::string& shaderSrc);
	Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int32 value) const;
	void SetFloat(const std::string& name, float value) const;
	void SetFloat3(const std::string& name, glm::vec3 value) const;
	void SetFloat4(const std::string& name, glm::vec4 value) const;
	void SetMat4(const std::string& name, const glm::mat4& matrix) const;

private:
	std::string ReadFile(const std::filesystem::path& path);
	std::unordered_map<GLuint, std::string> ParseShader(const std::string& file);
	void CreateProgram(const char* vertexSrc, const char* fragmentSrc);

	uint32 ShaderID;
};