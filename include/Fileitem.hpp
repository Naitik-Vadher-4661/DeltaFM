#pragma once
#include "Filesystemitem.hpp"


class Fileitem: public Filesystemitem{
    protected:
        std::string type;
    public:
        Fileitem(const fs::path& p):Filesystemitem(p){}
        std::string gettype() const;
        std::string getdisplaytext() const;
};
