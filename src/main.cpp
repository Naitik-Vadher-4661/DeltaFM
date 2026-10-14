#include <filesystem>
#include<iostream>
#include"../include//Filesystemitem.hpp"
using namespace std;

int main(){
    Filesystemitem testf(fs::current_path());

    cout<<"path: "<<testf.getpath().string()<<endl;
    cout<<"name: "<<testf.getname()<<endl;
    cout<<"size: "<<testf.getsize()<<endl;
    cout <<"items: "<<Filesystemitem::getitemcount()<<endl;


}
