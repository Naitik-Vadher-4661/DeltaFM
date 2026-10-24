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
std::string tabs="                                                             ";
if(display_name.length()<=20){
    display_name=name.substr(0,name.length())+std::string(20-name.length(),' ');
}
else{
display_name=name.substr(0,20);
}

full_line="📄 "+display_name+tabs.substr(0,30)+" -    "+tabs.substr(0,30)+modtime+tabs.substr(0,20)+type;
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
