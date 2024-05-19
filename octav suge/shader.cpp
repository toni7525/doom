#include "shader.h"

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>


//"shaders/Basic.shader"
shader::shader(const std::string& filepath)
    :FilePath(filepath),renderid(0)
{
    ShaderProgramSource source = ParseShader();
    renderid = CreateShader(source.VertexShader, source.FragmentShader);
}

shader::~shader()
{
    glDeleteProgram(renderid);
}

void shader::Bind()
{
    glUseProgram(renderid);
}

void shader::Unbind()
{
    glUseProgram(0);
}

void shader::SetUniform1i(const std::string& name, int v0)
{
    glUniform1i(GetUniformLocation(name), v0);
}

void shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

int shader::GetUniformLocation(const std::string& name)
{
    int location = glGetUniformLocation(renderid, name.c_str());
    if (location == -1)
        std::cout << "Waring uniform " << name << " dosent exist";
    return location;
}

ShaderProgramSource shader::ParseShader() {
    std::ifstream stream(FilePath);
    enum class Shadertype {
        NONE = -1,Vertex = 0, Fragment = 1
    };

    std::string line;
    std::stringstream ss[2];
    Shadertype type = Shadertype::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("Vertex") != std::string::npos) {
                type = Shadertype::Vertex;
               
            }else if (line.find("Fragment") != std::string::npos) {
                type = Shadertype::Fragment;
                
            }
        }
        else {
            ss[(int)type] << line << '\n';
        }
    }
    return { ss[0].str(),ss[1].str()};
}


unsigned int shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

void shader::SetUniform1f(const std::string& name, float v0)
{
    glUniform1f(GetUniformLocation(name), v0);
}
void shader::SetUniform2f(const std::string& name, float v0, float v1)
{
    glUniform2f(GetUniformLocation(name), v0,1);
}
void shader::SetUniform1b(const std::string& name, bool v0)
{
    glUniform1i(GetUniformLocation(name), v0);
}


unsigned int shader::CompileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int lenght;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);
        char* message = (char*)alloca(lenght * sizeof(char));
        glGetShaderInfoLog(id, lenght, &lenght, message);
        std::cout << "failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}