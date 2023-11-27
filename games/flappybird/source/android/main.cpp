#include "game/Bootstrap.hpp"

extern "C" {

struct android_app;
void startApplication(struct android_app *pApp);

void android_main(struct android_app *pApp) {
    bootstrap();
    startApplication(pApp);
}
}