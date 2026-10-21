#include "../include/Fileitem.hpp"
#include<format>
#include<chrono>
#include<cstdint>
std::string Fileitem:: gettype() const {

    if(cur_path.extension()== ".txt"){
        return "text";
    }
    else if(cur_path.extension()== ".jpg"||
        cur_path.extension()== ".png"||
        cur_path.extension()== "webp"||
        cur_path.extension()== ".jpeg")
    {
            return "image";
    }


    else if(cur_path.extension()== ".mp3"){ return "audio";}
    else if(cur_path.extension()== ".mp4"){return "video";}
    else if(cur_path.extension()== ".html"){return "html";}
    else if(cur_path.extension()== ".css"){return "css";}
    else if(cur_path.extension()== ".js"){return "Javascript";}
    else if(cur_path.extension()== ".c"){return "C";}
    else if(cur_path.extension()== ".cpp"){return "C++";}
return "uknown";
}
std::string Fileitem::getdisplaytext() {
std::string display_fileinfo;

std::string modtime=std::format("{:%Y-%m-%d %H:%M}", ftime);

//for size




std::string sz=formatsize(size);
return name+"                   "+modtime+"                 "+sz;

}

Fileitem::~Fileitem(){
    itemcount--;
}
Fileitem::Fileitem(const fs::path& p):Filesystemitem(p){
    itemcount++;
}
