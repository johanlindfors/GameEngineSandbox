#include "resources/Shader.h"
#include "utilities/GLHelper.h"
#include "glm/gtc/type_ptr.hpp"

using namespace std;
using namespace Engine;

Shader::~Shader() 
{
   GlDeleteProgram(ID);
}

void Shader::Use()
{
    GlUseProgram(ID);
}

void Shader::CreateShader(const string& name, const string& vertexShader, const string& fragmentShader)
{
    mName = name;
    ID = CompileProgram(vertexShader, fragmentShader);
}

void Shader::SetInteger(const string& name, int value)
{
    GlUniform1i(GlGetUniformLocation(ID, name.c_str()), value);
}

void Shader::SetVector2f(const string& name, float x, float y)
{
    GlUniform2f(GlGetUniformLocation(ID, name.c_str()), x, y);
}

void Shader::SetVector4f(const string& name, float x, float y, float z, float w)
{
    GlUniform4f(GlGetUniformLocation(ID, name.c_str()), x, y, z, w);
}

void Shader::SetMatrix4(const string& name, glm::mat4 &matrix)
{
    GlUniformMatrix4fv(GlGetUniformLocation(ID, name.c_str()), 1, false, glm::value_ptr(matrix));
}
