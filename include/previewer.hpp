// #pragma once
// #include<cstring>
// #include<vector>
// #include "Filemanager.hpp"
// class previewer: public Filemanager
// {
//     char text[500];
//     public:
//     previewer();
//     const char* preview();
// };

#pragma once
#include "Filemanager.hpp"

class previewer : public Filemanager {
    private:
        char text[500];
    public:
        previewer();
        void loadpreview();
        const char* preview();
};