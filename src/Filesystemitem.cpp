
#include<filesystem>
#include<cstdint>
#include "../include/Filesystemitem.hpp"
// namespace fs = std::filesystem;

int Filesystemitem::itemcount=0;     // declares the total objects


Filesystemitem::Filesystemitem(const fs::path& p){         // initialize the obj
    cur_path=p;
    name=p.filename().string();

    if(!fs::is_directory(p)){
    size=fs::file_size(p);
    }
    else{size=0;}


    per=fs::status(p).permissions();
    ftime=last_write_time(p);

    itemcount++;
}

std::string Filesystemitem::getname(){

    return name;
}

fs::path Filesystemitem::getpath(){
    return cur_path;
}

std::uintmax_t Filesystemitem::getsize(){
    return size;
}

fs::file_time_type Filesystemitem::getmodifytime(){
    return ftime;
}

bool Filesystemitem::operator<(const Filesystemitem& f) const{
    return (size<f.size);

}

 int Filesystemitem::getitemcount(){
    return itemcount;
}

Filesystemitem::~Filesystemitem() {
    itemcount--;
}
