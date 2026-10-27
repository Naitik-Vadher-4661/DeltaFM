#include "../include/Filemanager.hpp"
#include "../include/Fileitem.hpp"
#include "../include/Directoryitem.hpp"
#include "../include/Exception.hpp"

#include <filesystem>
#include <fstream>
#include <memory>
#include <iostream>
#include <algorithm>
#include <system_error>

Filemanager::Filemanager(fs::path initialpath){
    p=initialpath;
    totalitem=-1;
    selectedIndex=0;
    showhidden=false;
    loaddirectory();
}

 std::vector<std::unique_ptr<Filesystemitem>>& Filemanager::getitems(){
     return items;
 }

 int Filemanager::getselected(){return selectedIndex;}
 fs::path Filemanager::getpath(){return p;}

void Filemanager::loaddirectory(){

    items.clear();
    totalitem=-1;
    std::error_code ec;
    for(auto const& dir_item : fs::directory_iterator{p,fs::directory_options::skip_permission_denied, ec}){
        if(!dir_item.exists()) continue;
        if(!dir_item.is_directory()){
            if(showhidden){


            Fileitem f(dir_item);
            items.push_back(std::make_unique<Fileitem>(dir_item));
            totalitem++;
            }
            else{
                std::string n =dir_item.path().filename().string();
                if(n[0]=='.') continue;
                Fileitem f(dir_item);
                items.push_back(std::make_unique<Fileitem>(dir_item));
                totalitem++;
            }
        }
        else{
           if(showhidden){

               Directoryitem d(dir_item);
               items.push_back(std::make_unique<Directoryitem>(dir_item));
               totalitem++;
           }
           else{
               std::string n=dir_item.path().filename().string();
                if(n[0]=='.') continue;
                Directoryitem d(dir_item);
                items.push_back(std::make_unique<Directoryitem>(dir_item));
                totalitem++;
           }
        }
    }
defaultsortitem();

}

void Filemanager::moveup(){
    if(selectedIndex==0);
    else{
        selectedIndex--;
    }
}

void Filemanager::movedown(){
    if(selectedIndex<totalitem){
        selectedIndex++;
    }
    else{}
}

void Filemanager::gotochild(){

    if(items[selectedIndex]->gettype()=="Directory")
    {
        try{
            fs::perms perms = fs::status(items[selectedIndex]->getpath()).permissions();


                if ((perms & fs::perms::owner_read) == fs::perms::none ||
                    (perms & fs::perms::owner_write) == fs::perms::none ||
                    (perms & fs::perms::owner_exec) == fs::perms::none) {
                    throw PermissionDenied(items[selectedIndex]->getpath());
                }
                else{
                    throw 1;
                }
        }
        catch(int i){

            p=items[selectedIndex]->getpath();
             selectedIndex=0;
             loaddirectory();
    }

    }


}

void Filemanager::gotoparent(){

    if(!items.empty()){
     p=items[0]->getpath().parent_path().parent_path();

    selectedIndex=0;
    loaddirectory();
    }
    else{
        p=p.parent_path();
        selectedIndex=0;
        loaddirectory();
    }
}

void Filemanager::createfile(std::string file_name){
    try{
        for(auto const& dir_item : fs::directory_iterator{p}){
            if(file_name==dir_item.path().filename().string())
                throw AlreadyExists(dir_item.path());
        }
        throw 2;
    }
     catch(int i){
    std::ofstream newfile(p.string()+"/"+file_name);
    newfile.close();
    loaddirectory();
     }
}

void Filemanager::createfolder(std::string folder_name){
    try{
        for(auto const& dir_item : fs::directory_iterator{p}){
            if(folder_name==dir_item.path().filename().string())
                throw AlreadyExists(dir_item.path());
        }
        throw 2;
    }
     catch(int i){
         fs::create_directories(p.string()+"/"+folder_name);
         loaddirectory();
     }

}

void Filemanager::deleteselected(){


    fs::path p = items[selectedIndex]->getpath();

    std::error_code ec;
    fs::remove(p, ec);
    if (ec == std::errc::directory_not_empty){
        fs::remove_all(p);
    }
    else if (ec) {
        if (ec == std::errc::no_such_file_or_directory)
            throw NotFound(p);
        if (ec == std::errc::permission_denied ||
            ec == std::errc::operation_not_permitted)
            throw PermissionDenied(p);

        throw FileException(ec.message());
    }

    totalitem--;

    if(selectedIndex!=0) selectedIndex--;
    loaddirectory();
}

void Filemanager::renameselected(std::string new_name){
    try{
        for(auto const& dir_item : fs::directory_iterator{p}){
            if(new_name==dir_item.path().filename().string())
            {

                throw  AlreadyExists (dir_item.path()) ;
                break;
            }


        }
        throw 2;
    }

     catch(int i){
         fs::rename(items[selectedIndex]->getpath(),new_name);
      }

loaddirectory();
}

void swap(std::unique_ptr<Filesystemitem>& a, std::unique_ptr<Filesystemitem>& b) {
    a.swap(b);
}

void Filemanager::defaultsortitem() {
    std::stable_sort(items.begin(), items.end(),
        [](const std::unique_ptr<Filesystemitem>& a,
           const std::unique_ptr<Filesystemitem>& b) {
            return a->getname() < b->getname();
        });

}

void Filemanager::togglehidden(){
    if(showhidden==1){
        showhidden=0;
        loaddirectory();
    }
    else{
        showhidden=1;
        loaddirectory();
    }
}
