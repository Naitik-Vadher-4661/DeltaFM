#include"../include/Directoryitem.hpp"
#include<chrono>
#include<format>


std::string Directoryitem::gettype() const{
    return "Directory";
}

std::string Directoryitem::getdisplaytext() const{
    std::string cc=std::to_string(childcount) ;
    std::string modtime=std::format("{:%Y-%m-%d %H:%M}", ftime);
    return cc+" "+modtime;
}

Directoryitem::Directoryitem(fs::path dp):Filesystemitem(dp){
  itemcount++;
   childcount=0;
   for (auto const& dir_entry : std::filesystem::directory_iterator{dp}){

       childcount++;
   }
}

Directoryitem::~Directoryitem(){
    itemcount--;
}

int Directoryitem::getcc(){return childcount;}
