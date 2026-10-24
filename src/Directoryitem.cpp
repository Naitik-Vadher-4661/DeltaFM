#include"../include/Directoryitem.hpp"
#include<chrono>
#include<format>


std::string Directoryitem::gettype() const{
    return "Directory";
}

std::string Directoryitem::getdisplaytext() {
    std::string cc=std::to_string(childcount) ;
    std::string modtime=std::format("{:%Y-%m-%d %H:%M}", ftime);
    std::string display_name=name;
    std::string full_line;
    std::string tabs="                                                             ";
    if(display_name.length()<=20){
        display_name=name.substr(0,name.length()) +"/"+std::string(20-name.length(),' ');
    }
    else{
   display_name=name.substr(0,20)+"/";
    }
    cc=tabs.substr(0,30)+cc+std::string(5-cc.length(),' ')+tabs.substr(0,30);

    full_line=display_name+cc+modtime+tabs.substr(0,20)+"directory";
    return full_line;
}

Directoryitem::Directoryitem(fs::path dp):Filesystemitem(dp){
  itemcount++;
   childcount=0;
   std::error_code ec;
   fs::directory_iterator it(dp, ec);
   if (!ec) {
       for (; it != fs::directory_iterator(); it.increment(ec)) {
           if (ec) break;
           childcount++;
       }
   }
}

Directoryitem::~Directoryitem(){
    itemcount--;
}

int Directoryitem::getcc(){return childcount;}
