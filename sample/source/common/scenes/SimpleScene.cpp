#include "SimpleScene.h"
#include "utilities/IOC.hpp"
#include "renderers/SimpleRenderer.h"

using namespace std;
using namespace Engine;
using namespace Sample;

void SimpleScene::draw(shared_ptr<IRenderer> renderer)
{
    auto simpleRenderer = static_pointer_cast<SimpleRenderer>(renderer);
    if(simpleRenderer.get()){
        simpleRenderer->draw();
    }
}
