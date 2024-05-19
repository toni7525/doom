#pragma once
#include <string>
#include<GL/glew.h>

struct ShaderProgramSource
{
	std::string VertexShader;
	std::string FragmentShader;
};

class shader {
private:
	std::string FilePath;
	unsigned int renderid;
public:
	shader(const std::string& filepath);
	~shader();

	void Bind();
	void Unbind();
	void SetUniform1i(const std::string& name, int v0);
	void SetUniform1f(const std::string& name, float v0);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniform2f(const std::string& name, float v0, float v1);
	void SetUniform1b(const std::string& name, bool v0);

private:
	int GetUniformLocation(const std::string& name);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	ShaderProgramSource ParseShader();
};