#include "../include/Fileitem.hpp"
#include<format>
#include<chrono>
#include<magic.h>

//#include<cstdint>
std::string Fileitem:: gettype() const {
return type;

}
std::string Fileitem::getdisplaytext() {

std::string full_line;
std::string modtime=std::format("{:%Y-%m-%d %H:%M}", ftime);
std::string sz=formatsize(size);
std::string display_name=name;
if(name.length()>24){
display_name=name.substr(0,20)+"....";
}

std::ostringstream oss;
oss << "📄 "
    << std::left << std::setw(25) << display_name
    << std::setw(12) << formatsize(size)
    << std::setw(20) << modtime
    << type;
full_line = oss.str();
return full_line;

}

Fileitem::~Fileitem(){
    itemcount--;
}
Fileitem::Fileitem(const fs::path& p):Filesystemitem(p){
    itemcount++;


    std::string pathstr = p.string();
    type = "File";

    magic_t magic = magic_open(MAGIC_MIME_TYPE);
    if (magic != nullptr) {
        if (magic_load(magic, nullptr) == 0) {
            const char* result = magic_file(magic, pathstr.c_str());
            if (result != nullptr) {
                type = result;
            }
        }
        magic_close(magic);

     }
}
