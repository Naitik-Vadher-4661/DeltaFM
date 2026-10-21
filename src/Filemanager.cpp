#include "../include/Filemanager.hpp"
#include "../include/Fileitem.hpp"
#include "../include/Directoryitem.hpp"
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
           if(showhidden){
               Directoryitem d(dir_item);
               items.push_back(std::make_unique<Directoryitem>(dir_item));
           }
           else{
               std::string n=dir_item.path().filename().string();
                if(n[0]=='.') continue;
                Directoryitem d(dir_item);
                items.push_back(std::make_unique<Directoryitem>(dir_item));
           }
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
    Directoryitem d(fs::current_path());
    int cur_dir_count=d.getitemcount();
    if(selectedIndex<cur_dir_count){
        selectedIndex++;
    }
}

void Filemanager::gotochild(){
    if(items[selectedIndex]->gettype()=="folder")
    p=items[selectedIndex]->getpath();
loaddirectory();
}

void Filemanager::gotoparent(){
    p=p.parent_path();
    loaddirectory();
}

void Filemanager::createfile(std::string file_name){
    std::ofstream newfile(file_name);
    newfile.close();
    items.push_back(std::make_unique<Fileitem>(file_name));
}

void Filemanager::createfolder(std::string folder_name){
    fs::create_directories(folder_name);
    items.push_back(std::make_unique<Directoryitem>(folder_name));
}

void Filemanager::deleteselected(){
    fs::remove(items[selectedIndex]->getpath());

}

void Filemanager::renameselected(std::string new_name){
    fs::rename(items[selectedIndex]->getpath(),new_name);
}

void Filemanager::sortitem(std::string sorttype="name"){
    Directoryitem d(fs::current_path());
    int cur_dir_count=d.getitemcount();

    // sort by name
    if(sorttype=="name"){
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
    }
    else if(sorttype=="size"){
        for (int i=0;i<cur_dir_count;i++){
            if(items[i]<items[i+1])
                items[i].swap(items[i+1]);
        }
    }
}

void Filemanager::togglehidden(){
    if(showhidden==1)
        showhidden=0;
    else{
        showhidden=1;
    }
}
