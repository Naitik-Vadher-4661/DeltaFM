#include"../include/Directoryitem.hpp"
#include<chrono>
#include<format>


std::string Directoryitem::gettype() const{
    return "Directory";
}

std::string Directoryitem::getdisplaytext() {
    std::string cc=std::to_string(childcount) ;
    std::string modtime=std::format("{:%Y-%m-%d %H:%M}", ftime);
    return name+"/"+"               Directory"+"           "+cc+"               "+modtime;
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
