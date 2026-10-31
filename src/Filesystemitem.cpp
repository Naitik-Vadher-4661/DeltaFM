

#include "../include/Filesystemitem.hpp"
#include "../include/Exception.hpp"
#include <filesystem>
#include<exception>
// namespace fs = std::filesystem;   this is commented because include fsi.hpp has already declared fs

int Filesystemitem::itemcount=0;     // declares the total objects


Filesystemitem::Filesystemitem(const fs::path& p){         // initialize the obj
    cur_path=p;
    name=p.filename().string();
        try{
            if(std::filesystem::exists(p)){
                throw 2;
            }
            else{
                throw NotFound(p);
            }
        }
        catch(int i){
            ftime=last_write_time(p);
            ftime=ftime+std::chrono::hours(5)+std::chrono::minutes(30);
            per=fs::status(p).permissions();
            if(!fs::is_directory(p)){

                try{
                size=fs::file_size(p);

                }
                catch (fs::filesystem_error& e)
                   {
                       size=0;
                   }
            }
            else{size=0;}

}
}






std::string Filesystemitem::getname()const {

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

std::string Filesystemitem::getperms(){
    using std::filesystem::perms;
    std::string s;

    auto show = [&](std::string op, perms perm)
    {

        s+=(perms::none == (per) ? "-" : op);
    };
    show("r", perms::owner_read);
    show("w", perms::owner_write);
    show("x", perms::owner_exec);
    show("r", perms::group_read);
    show("w", perms::group_write);
    show("x", perms::group_exec);
    show("r", perms::others_read);
    show("w", perms::others_write);
    show("x", perms::others_exec);
    return s;
}

std::string Filesystemitem::formatsize(std::uintmax_t bytes) {
       const char* units[] = {"B", "KB", "MB", "GB", "TB"};
       double value = static_cast<double>(bytes);
       int unit = 0;
       while (value >= 1024.0 && unit < 4) {
           value /= 1024.0;
           unit++;
       }
       std::ostringstream out;
       if (unit == 0)
           out << bytes << " B";
       else
           out << std::fixed << std::setprecision(1) << value << " " << units[unit];
       return out.str();
   }
