#pragma once
#include<filesystem>
#include<cstdint>
#include<string>
#include<iomanip>
#include<sstream>
 namespace fs=std::filesystem;

 class Filesystemitem{

protected:
        std::string name;               // this stores the file name
        fs::path cur_path;                  // this is for current path of file/directory
        std::uintmax_t size;            //this is uintmax_t to store the size
        fs::perms per;                      //this is for file/folder permission
        fs::file_time_type ftime;           //thos is for last modify time;
        static int itemcount;           //this is intem counte that how much items are there in whole filesystem
public:
        Filesystemitem(const fs::path& p);
        std::string getname() const;  //return file/folder name
        fs::path getpath();        // return path of the file/folder
        std::uintmax_t getsize();  //returns the size
       fs::file_time_type getmodifytime();   // return lasr modify time
        virtual std::string gettype() const = 0;   // this is for the type file or directory
        virtual std::string getdisplaytext()  = 0; // this is for displaying content of file
        virtual ~Filesystemitem();   // destructor
        bool operator<(const Filesystemitem&) const ;   // this is for the sorting of file/folder
        static int getitemcount();  // this returns the itemcount
        std::string formatsize(std::uintmax_t bytes);
        std::string getperms();  //this retrun the permissions
 };
