#include "resources/Shader.h"
#include "utilities/GLHelper.h"

using namespace glm;
using namespace std;
using namespace Engine;

Shader::~Shader() 
{
    glDeleteProgram(ID);
}

void Shader::Use()
{
    glUseProgram(ID);
}

void Shader::CreateShader(const string& name, const string& vertexShader, const string& fragmentShader)
{
    mName = name;
    ID = CompileProgram(vertexShader, fragmentShader);
}

void Shader::SetInteger(const string& name, int value)
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::SetVector2f(const string& name, float x, float y)
{
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}

void Shader::SetVector4f(const string& name, float x, float y, float z, float w)
{
    glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}

void Shader::SetMatrix4(const string& name, glm::mat4 &matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, false, value_ptr(matrix));
}
