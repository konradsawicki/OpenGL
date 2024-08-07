#include <glad/glad.h>
#include "Core.h"

#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>


namespace yon {

enum class ShaderType {
  NONE = -1, VERTEX = 0, FRAGMENT = 1
};

Shader::Shader(const std::string& filepath)
	: m_filePath(filepath), m_rendererID(0) {
  ShaderProgramSource source = ParseShader(filepath);
  m_rendererID = CreateShader(source.vertexSource, source.fragmentSource);
}

Shader::~Shader() {
  GLCall(glDeleteProgram(m_rendererID));
}

void Shader::Bind() const {
  GLCall(glUseProgram(m_rendererID));
}

void Shader::Unbind() const {
  GLCall(glUseProgram(0));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
  GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniformMat4(const std::string& name, glm::mat4 matrix) {
  auto temp = GetUniformLocation(name);
  GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, (const GLfloat*)&matrix));
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath) {
  std::ifstream stream(filepath);

  std::string line;
  std::stringstream ss[2];
  ShaderType type = ShaderType::NONE;

  while (getline(stream, line)) {
    if (line.find("#shader") != std::string::npos) {
      if (line.find("vertex") != std::string::npos)
        type = ShaderType::VERTEX;
      else if (line.find("fragment") != std::string::npos)
        type = ShaderType::FRAGMENT;
    }
    else {
      ss[(int)type] << line << '\n';
    }
  }

  return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
  unsigned int program = glCreateProgram();
  unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
  unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

  GLCall(glAttachShader(program, vs));
  GLCall(glAttachShader(program, fs));
  GLCall(glLinkProgram(program));
  GLCall(glValidateProgram(program));

  GLCall(glDeleteShader(vs));
  GLCall(glDeleteShader(fs));

  return program;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
  unsigned int id = glCreateShader(type);
  const char* src = source.c_str();
  GLCall(glShaderSource(id, 1, &src, nullptr));
  GLCall(glCompileShader(id));

  int result;
  GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
  if (result == GL_FALSE) {
    int length;
    GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
    char* message = new char[length];
    GLCall(glGetShaderInfoLog(id, length, &length, message));
    std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader\n";
    std::cout << message << std::endl;
    delete[] message;
    GLCall(glDeleteShader(id));
    return 0;
  }
  return id;
}


int Shader::GetUniformLocation(const std::string& name) {
  if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
    return m_uniformLocationCache[name];
  GLCall(int location = glGetUniformLocation(m_rendererID, name.c_str()));
  if (location == -1)
    std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;

  m_uniformLocationCache[name] = location;
  return location;
}

}