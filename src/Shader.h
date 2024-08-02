#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <unordered_map>
#include "glm/glm.hpp"

namespace yon {

struct ShaderProgramSource {
	std::string vertexSource;
	std::string fragmentSource;
};

class Shader {
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4(const std::string& name, glm::mat4);

private:
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	int GetUniformLocation(const std::string& name);

private:
	unsigned int m_rendererID;
	std::string m_filePath;
	std::unordered_map<std::string, unsigned int> m_uniformLocationCache;
};

}

#endif