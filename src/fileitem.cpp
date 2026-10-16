#include "../include/fileitem.hpp"
#include<fstream>

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
std::string Fileitem::getdisplaytext() const{
   std::fstream file(cur_path);
   std::string fline;
   while (std::getline(file, fline) && fline.empty()) {

   }
   return fline ;

}
