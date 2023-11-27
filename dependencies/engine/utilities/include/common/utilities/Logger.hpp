#pragma once

#include <sstream>

/*!
 * Use this to log strings out to logcat. Note that you should use std::endl to commit the line
 *
 * ex:
 *  aout << "Hello World" << std::endl;
 */
extern std::ostream debuglog;