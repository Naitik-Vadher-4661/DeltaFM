#include "../include/Filemanager.hpp"
#include "../include/Fileitem.hpp"
#include <filesystem>

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
            //directory load logic
        }
    }

}
