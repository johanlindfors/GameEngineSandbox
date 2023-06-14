#pragma once
#include <vector>
#include "objects/Crate.hpp"

namespace Engine
{
    class IRenderer;
}

class Map {
    public:
        Map();
        ~Map();
        void initialize();
        void draw(std::shared_ptr<Engine::IRenderer> renderer);

    private:
        std::vector<char> mLevel;
        std::vector<Crate> mCrates;
};