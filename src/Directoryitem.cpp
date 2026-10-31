#include"../include/Directoryitem.hpp"
#include<chrono>
#include<format>


std::string Directoryitem::gettype() const{
    return "Directory";
}

std::string Directoryitem::getdisplaytext() {
    std::string cc=std::to_string(childcount)+" items" ;
    std::string modtime=std::format("{:%Y-%m-%d %H:%M}", ftime);
    std::string full_line;
    std::string display_name=name;
    if(name.length()>24){
      display_name=name.substr(0,20)+"....";
    }
   std::ostringstream oss;

    oss << "📁 "
        << std::left << std::setw(25) << display_name
        << std::setw(12) << cc
        << std::setw(20) << modtime
        << "Directory";
    full_line=oss.str();
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
