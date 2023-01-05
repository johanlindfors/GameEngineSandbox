#include "resources/ShaderBase.h"
#include "resources/Model.h"

using namespace Engine;

GLuint ShaderBase::loadShader(
    const std::string &vertexSource,
    const std::string &fragmentSource) 
{
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertexSource);
    if (!vertexShader) {
        return -1;
    }

    GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentSource);
    if (!fragmentShader) {
        glDeleteShader(vertexShader);
        return -1;
    }

    GLuint program = glCreateProgram();
    if (program) {
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);

        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
        if (linkStatus != GL_TRUE) {
            printf("Failed to link\n");
            GLint logLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

            // If we fail to link the shader program, log the result for debugging
            if (logLength) {
                GLchar *log = new GLchar[logLength];
                glGetProgramInfoLog(program, logLength, nullptr, log);
                // aout << "Failed to link program with:\n" << log << std::endl;
                delete[] log;
            }

            glDeleteProgram(program);
        }
    }
    // The shaders are no longer needed once the program is linked. Release their memory.
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}


GLuint ShaderBase::loadShader(GLenum shaderType, const std::string &shaderSource) {
    GLuint shader = glCreateShader(shaderType);
    if (shader) {
        auto *shaderRawString = (GLchar *) shaderSource.c_str();
        GLint shaderLength = shaderSource.length();
        glShaderSource(shader, 1, &shaderRawString, &shaderLength);
        glCompileShader(shader);

        GLint shaderCompiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderCompiled);

        // If the shader doesn't compile, log the result to the terminal for debugging
        if (!shaderCompiled) {
            GLint infoLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLength);

            if (infoLength) {
                auto *infoLog = new GLchar[infoLength];
                glGetShaderInfoLog(shader, infoLength, nullptr, infoLog);
                //aout << "Failed to compile with:\n" << infoLog << std::endl;
                delete[] infoLog;
            }

            glDeleteShader(shader);
            shader = 0;
        }
    }
    return shader;
}

void ShaderBase::activate() const {
    glUseProgram(mProgram);
}

void ShaderBase::deactivate() const {
    glUseProgram(0);
}

void ShaderBase::drawModel(const Model &model) const {
    // The position attribute is 3 floats
    glVertexAttribPointer(
            mPosition, // attrib
            3, // elements
            GL_FLOAT, // of type float
            GL_FALSE, // don't normalize
            sizeof(Utilities::Vertex), // stride is Vertex bytes
            model.getVertexData() // pull from the start of the vertex data
    );
    glEnableVertexAttribArray(mPosition);

    // The uv attribute is 2 floats
    glVertexAttribPointer(
            mUv, // attrib
            2, // elements
            GL_FLOAT, // of type float
            GL_FALSE, // don't normalize
            sizeof(Utilities::Vertex), // stride is Vertex bytes
            ((uint8_t *) model.getVertexData()) + sizeof(Utilities::Vector3) // offset Vector3 from the start
    );
    glEnableVertexAttribArray(mUv);

    // Setup the texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, model.getTexture().textureIndex);

    // Draw as indexed triangles
    glDrawElements(GL_TRIANGLES, model.getIndexCount(), GL_UNSIGNED_SHORT, model.getIndexData());

    glDisableVertexAttribArray(mUv);
    glDisableVertexAttribArray(mPosition);
}
