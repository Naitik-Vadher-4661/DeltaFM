
#include <filesystem>
#include<iostream>
#include"../include/Filesystemitem.hpp"
#include "../include/Fileitem.hpp"
#include "../include/Directoryitem.hpp"
#include "../include/Filemanager.hpp"
#include "../include/previewer.hpp"
using namespace std;

int main(){
    fs::path p="/home/known/DeltaFM/src/main.cpp";
   Fileitem testf(p);

    cout<<"path: "<<testf.getpath().string()<<endl;
    cout<<"name: "<<testf.getname()<<endl;
    cout<<"size: "<<testf.getsize()<<" KB"<<endl;
    cout <<"items: "<<Filesystemitem::getitemcount()<<endl;
    cout<<"File type : "<<testf.gettype()<<endl;
    cout<<"initial Text :"<<testf.getdisplaytext()<<endl;
    Filemanager fm;
    fm.createfolder("nik");
    Directoryitem d("nik");
  cout<<"info abot directory : "<<d.gettype()<<" " <<d.getdisplaytext()<<" "<<d.getcc()<<endl;
  cout<<"item count : "<<d.getitemcount()<<endl;

  previewer test;
  cout<<test.preview()<<endl;

}
