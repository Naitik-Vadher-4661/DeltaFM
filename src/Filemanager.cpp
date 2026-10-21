#include "../include/Filemanager.hpp"
#include "../include/Fileitem.hpp"
#include "../include/Directoryitem.hpp"
#include "../include/Exception.hpp"
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <memory>
#include <iostream>

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
    for(auto const& dir_item : fs::directory_iterator{p}){
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

    p=items[selectedIndex]->getpath();
     selectedIndex=0;
     loaddirectory();
    }


}

void Filemanager::gotoparent(){

    p=p.parent_path();
    selectedIndex=0;
    loaddirectory();

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

void Filemanager::sortitem(){
    Directoryitem d(fs::current_path());
    int cur_dir_count=d.getitemcount();

    // sort by name

        std::string max=items[0]->getpath().filename().string();

        for(int i=0;i<cur_dir_count  ;i++){

            std::string cmp=items[i]->getpath().filename().string();
            if(max[0]<cmp[i]){
                items[0].swap(items[i]);
                max=items[0]->getpath().filename().string();
            }
            else{
                continue;
            }
        }


loaddirectory();
}

void Filemanager::togglehidden(){
    if(showhidden==1)
        showhidden=0;
    else{
        showhidden=1;
    }
}
