#pragma once

#include <iostream>
#include <sstream>

/*!
 * Use this class to create an output stream that writes to logcat. By default, a global one is
 * defined as @a aout
 */
class EmscriptenOut: public std::stringbuf {
public:
    /*!
     * Creates a new output stream for logcat
     * @param kLogTag the log tag to output
     */
    inline EmscriptenOut(const char* kLogTag) : logTag_(kLogTag){}

protected:
    virtual int sync() override {
        std::cout << logTag_ << str().c_str();
        str("");
        return 0;
    }

private:
    const char* logTag_;
};
