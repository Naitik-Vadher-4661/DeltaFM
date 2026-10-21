#pragma once
#include "Filemanager.hpp"

class previewer : public Filemanager {
    private:
        char text[500];
    public:
        previewer(std::filesystem::path);
        const char* preview();
};
