#include "../include/Filemanager.hpp"
#include "../include/Fileitem.hpp"
#include "../include/Directoryitem.hpp"
#include "../include/Exception.hpp"
#include <cstdlib>
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
        std::error_code stat_ec;
        if(!dir_item.is_directory()){
            if(showhidden){

                if(stat_ec){
                    continue;
                }
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
               fs::perms perms = fs::status(dir_item).permissions();

               if(stat_ec){
                   continue;
               }

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
    for(int i=0;i<totalitem;i++){
    try{
        fs::perms perms = fs::status(items[i]->getpath()).permissions();


            if ((perms & fs::perms::owner_read) == fs::perms::none ||
                (perms & fs::perms::owner_write) == fs::perms::none ||
                (perms & fs::perms::owner_exec) == fs::perms::none) {
                if (i==totalitem-1)throw PermissionDenied(items[selectedIndex]->getpath());
                continue;
            }
            else{
                throw 1;
            }
    }
    catch(int i){
    p=p.parent_path();
    selectedIndex=0;
    loaddirectory();
    }
    }
}

void Filemanager::createfile(std::string file_name){
    try{
        for(auto const& dir_item : fs::directory_iterator{p}){
            if(file_name==dir_item.path().filename().string())
                throw AlreadyExists(dir_item.path());
        }
    }
     catch(FileException f){
         std::cout<<f.what()<<std::endl;
     }
    std::ofstream newfile(file_name);
    newfile.close();
    items.push_back(std::make_unique<Fileitem>(file_name));
}

void Filemanager::createfolder(std::string folder_name){
    try{
        for(auto const& dir_item : fs::directory_iterator{p}){
            if(folder_name==dir_item.path().filename().string())
                throw AlreadyExists(dir_item.path());
        }
    }
     catch(FileException f){

     }
    fs::create_directories(folder_name);
    totalitem++;
    items.push_back(std::make_unique<Directoryitem>(folder_name));
    loaddirectory();
}

void Filemanager::deleteselected(){
    // try{
    //     for(int i=0;i<selectedIndex;i++){
    //         // if(items[i]->getperms()=)
    //     }
    // }
    fs::remove(items[selectedIndex]->getpath());
    totalitem--;
    loaddirectory();
}

void Filemanager::renameselected(std::string new_name){
    try{
        for(auto const& dir_item : fs::directory_iterator{p}){
            if(new_name==dir_item.path().filename().string())
            {

                throw  AlreadyExists (dir_item.path()) ;

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
