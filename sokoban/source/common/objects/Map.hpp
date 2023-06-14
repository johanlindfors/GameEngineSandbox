#pragma once
#include <vector>
#include "objects/Crate.hpp"

class Map {
    public:
        Map();
        ~Map();
        void initialize();

    private:
        std::vector<char> mLevel;
        std::vector<Crate> mCrates;
};