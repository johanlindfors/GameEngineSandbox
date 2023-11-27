#pragma once

struct android_app;

class AndroidWrapper {
public:
    AndroidWrapper(android_app* app)
            : instance(app) { }
    android_app* GetInstance() {
        return instance;
    }

private:
    android_app *instance;
};