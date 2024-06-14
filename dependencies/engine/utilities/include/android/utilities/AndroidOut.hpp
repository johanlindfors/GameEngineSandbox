#pragma once

#include <android/log.h>
#include <sstream>

/*!
 * Use this class to create an output stream that writes to logcat. By default, a global one is
 * defined as @a aout
 */
class AndroidOut: public std::stringbuf {
public:
    /*!
     * Creates a new output stream for logcat
     * @param kLogTag the log tag to output
     */
    inline AndroidOut(const char* kLogTag) : logTag_(kLogTag){}

protected:
    virtual int sync() override {
#ifdef _DEBUG
        __android_log_print(ANDROID_LOG_DEBUG, logTag_, "%s", str().c_str());
        str("");
#endif
        return 0;
    }

private:
    const char* logTag_;
};
