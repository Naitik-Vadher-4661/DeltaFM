
#include <filesystem>
#include<iostream>
#include"../include/Filesystemitem.hpp"
#include "../include/Fileitem.hpp"
#include "../include/Filemanager.hpp"
using namespace std;

int main(){
    fs::path p="/home/naitik/Documents/projects/DeltaFM/src/main.cpp";
   Fileitem testf(p);

    cout<<"path: "<<testf.getpath().string()<<endl;
    cout<<"name: "<<testf.getname()<<endl;
    cout<<"size: "<<testf.getsize()<<" KB"<<endl;
    cout <<"items: "<<Filesystemitem::getitemcount()<<endl;
    cout<<"File type : "<<testf.gettype()<<endl;
    cout<<"initial Text :"<<testf.getdisplaytext()<<endl;


}
