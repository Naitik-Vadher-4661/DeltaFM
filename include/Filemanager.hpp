#pragma once
#include "Filesystemitem.hpp"
#include <vector>

class Filemanager{
    protected:
        fs::path p;
        std::vector<std::unique_ptr<Filesystemitem>> items;
        int selectedIndex;
        bool showhidden;
        int totalitem;
    public:
        Filemanager(fs::path intialpath);
        void loaddirectory();
        int getselected();
        fs::path getpath();
        std::vector<std::unique_ptr<Filesystemitem>>& getitems();
        void moveup();
        void movedown();
        void gotochild();
        void gotoparent();
        void createfile(std::string);
        void createfolder(std::string);
        void deleteselected();
        void renameselected(std::string);
        void sortitem();
        void togglehidden();

};
