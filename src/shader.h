#pragma once
#include <string>
#include <unordered_map>
#include "glm/glm.hpp"

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{

public:
	Shader(const std::string &filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;
	void SetUniform1i(const std::string &name, int value);
	void SetUniform1f(const std::string &name, float value);
	void SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string &name, const glm::mat4 &matrix);

private:
	unsigned int RendererID;
	std::string Filepath;
	std::unordered_map<std::string, int> UniformLocationCache;

	int GetUniformLocation(const std::string &name);

	ShaderProgramSource ParseShader(const std::string &filepath);
	unsigned int CreateShader(const std::string &vertexShader, const std::string fragmentShader);
	unsigned int CompileShader(unsigned int type, const std::string &source);
};
