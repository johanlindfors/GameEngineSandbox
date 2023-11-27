#pragma once

#define GLFW_INCLUDE_ES2
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include "utilities/Logger.hpp"

//! executes glGetString and outputs the result to logcat
#define PRINT_GL_STRING(s) { debuglog << #s": "<< glGetString(s) << std::endl;}

/*!
 * @brief if glGetString returns a space separated list of elements, prints each one on a new line
 *
 * This works by creating an istringstream of the input c-style string. Then that is used to create
 * a vector -- each element of the vector is a new element in the input string. Finally a foreach
 * loop consumes this and outputs it to logcat using @a aout
 */
#define PRINT_GL_STRING_AS_LIST(s) { \
std::istringstream extensionStream((const char *) glGetString(s));\
std::vector<std::string> extensionList(\
        std::istream_iterator<std::string>{extensionStream},\
        std::istream_iterator<std::string>());\
debuglog << #s":\n";\
for (auto& extension: extensionList) {\
    debuglog << extension << "\n";\
}\
debuglog << std::endl;\
}
