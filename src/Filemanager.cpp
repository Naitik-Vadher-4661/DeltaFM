#include "../include/Filemanager.hpp"
#include "../include/Fileitem.hpp"
#include <filesystem>
#include <fstream>
#include <memory>

Filemanager::Filemanager(){
    p=fs::current_path();
    selectedIndex=0;
    showhidden=false;
    loaddirectory();
}

void Filemanager::loaddirectory(){
    items.clear();
    for(auto const& dir_item : fs::directory_iterator{p}){
        if(!dir_item.is_directory()){
            if(showhidden){
            Fileitem f(dir_item);
            items.push_back(std::make_unique<Fileitem>(dir_item));
            }
            else{
                std::string n =dir_item.path().filename().string();
                if(n[0]=='.') continue;
                Fileitem f(dir_item);

                items.push_back(std::make_unique<Fileitem>(dir_item));
            }
        }
        else{
           //directory logic goes here
        }
    }

}

void Filemanager::moveup(){
    if(selectedIndex);
    else{
        selectedIndex--;
    }
}

void Filemanager::movedown(){
    //here needs total items first for the move down
}

void Filemanager::gotochild(){
    if(items[selectedIndex]->gettype()=="folder")
    p=items[selectedIndex]->getpath();
}

void Filemanager::gotoparent(){
    p=p.parent_path();
}

void Filemanager::createfile(std::string file_name){
    std::ofstream newfile(file_name);
    newfile.close();
}

void Filemanager::createfolder(std::string folder_name){
    fs::create_directories(folder_name);
}

void Filemanager::deleteselected(){
    fs::remove(items[selectedIndex]->getpath());

}

void Filemanager::renameselected(std::string new_name){
    fs::rename(items[selectedIndex]->getpath(),new_name);
}

void Filemanager::sortitem(){
    std::string max=items[0]->getpath().filename().string();

    // for(int i=0;i<  ;i++){

    // std::string cmp=items[i]->getpath().filename().string();
    // if(max[0]<cmp[i]){
    //     items[0].swap(items[i]);
    //     max=items[0]->getpath().filename().string();

    // }
    // here we first need directory item class's total items;

}

void Filemanager::togglehidden(){
    if(showhidden==1)
        showhidden=0;
    else{
        showhidden=1;
    }
}
