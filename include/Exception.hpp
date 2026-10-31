#pragma once
#include "previewer.hpp"
#include <exception>
#include<string>
#include<filesystem>

namespace fs =std::filesystem ;

class FileException:public std::exception{
    protected:
        std::string errmsg;
    public:
        FileException(const std::string msg){
            errmsg=msg;
        }
        const char * what() const noexcept override{
         return errmsg.c_str();
        }
};

class NotFound: public FileException{

  public:
    NotFound(fs::path p):FileException(p.filename().string()+" does not exist!"){}
};

class PermissionDenied : public FileException{

    public:
        PermissionDenied(fs::path p):FileException( "Can't access " +p.filename().string()+" ,Permission Denied!"){}

};

class AlreadyExists : public FileException{
    public:
        AlreadyExists(fs::path p):FileException(p.filename().string()+" already exist!"){}
};
