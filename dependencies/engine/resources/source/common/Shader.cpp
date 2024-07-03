#include "resources/Shader.hpp"
#include "utilities/GLHelper.hpp"
#include "utilities/Logger.hpp"
#include "glm/gtc/type_ptr.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

Shader::~Shader()
{
    debuglog << "[Shader::~Shader]" << endl;
    GlDeleteProgram(ID);
}

void Shader::use()
{
    GlUseProgram(ID);
}

void Shader::createShader(const string &name, const string &vertexShader, const string &fragmentShader)
{
    mName = name;
    ID = compileProgram(vertexShader, fragmentShader);
}

void Shader::setBoolean(const string &name, bool value)
{
    GlUniform1i(GlGetUniformLocation(ID, name.c_str()), value ? 1 : 0);
}

void Shader::setInteger(const string &name, int value)
{
    GlUniform1i(GlGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVector2f(const string &name, float x, float y)
{
    GlUniform2f(GlGetUniformLocation(ID, name.c_str()), x, y);
}

void Shader::setVector3f(const string &name, float x, float y, float z)
{
    GlUniform3f(GlGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::setVector4f(const string &name, float x, float y, float z, float w)
{
    GlUniform4f(GlGetUniformLocation(ID, name.c_str()), x, y, z, w);
}

void Shader::setVector4fv(const string &name, Vector4 vec)
{
    GlUniform4f(GlGetUniformLocation(ID, name.c_str()), vec.x, vec.y, vec.z, vec.w);
}

void Shader::setMatrix4(const string &name, const glm::mat4 &matrix)
{
    GlUniformMatrix4fv(GlGetUniformLocation(ID, name.c_str()), 1, false, glm::value_ptr(matrix));
}

int Shader::getAttribLocation(const string &name) const {
    return GlGetAttribLocation(ID, name.c_str());
}