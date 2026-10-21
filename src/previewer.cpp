// #include "../include/previewer.hpp"
// #include<fstream>
// #include<cstring>
// previewer::previewer()
// {
//     char line[100];
//     int count=0;
//     if(items[selectedIndex]->gettype()=="Directory")
//     {
//         strcpy(text, "This is a directory");
//         exit;
//     }
//     std::string ext=items[selectedIndex]->gettype();
//     if(ext==".jpg"||ext==".jpeg"||ext==".png"||ext==".gif"||ext==".mp3"||ext==".mp4"||ext==".webp"||ext==".mkv" || ext=="unknown")
//     {
//         strcpy(text, "Preview not available");
//         exit;
//     }
//     std::ifstream file(items[selectedIndex]->getpath());
//     if(!file)
//     {
//         strcpy(text, "Unable to open for preview");
//         exit;
//     }
//     while(count<5 && file.getline(line, 100))
//     {
//         strcat(text, line);
//         strcat(text, "\n");
//         count++;
//     }
//     file.close();
// }
// const char* previewer::preview()
// {
//     return text;
// }



#include "../include/previewer.hpp"
#include <filesystem>
#include <fstream>
#include <cstring>
#include <string>

previewer::previewer()
{
    text[0] = '\0';      
    loadpreview();      
}

void previewer::loadpreview()
{
    text[0] = '\0';

  

    fs::path path = items[selectedIndex]->getpath();
    std::error_code ec;

    if (fs::is_directory(path, ec))
    {
        strcpy(text, "This is a directory");
        return;
    }

    std::string ext = path.extension().string();
    for (char& c : ext)
    {
        if (c >= 'A' && c <= 'Z') c += 32;
    }


    if (ext == ".jpg" || ext == ".jpeg" || ext == ".png" || ext == ".gif" ||
        ext == ".webp" || ext == ".mp3" || ext == ".mp4" || ext == ".mkv")
    {
        strcpy(text, "Preview not available");
        return;
    }


    std::ifstream file(path);
    if (!file)
    {
        strcpy(text, "Unable to open for preview");
        return;
    }


    std::string line;
    int count = 0;                                
    while (count < 5 && std::getline(file, line))
    {
        line += "\n";
        int space = sizeof(text) - strlen(text) - 1;
        if (space <= 0) break;              
        strncat(text, line.c_str(), space);
        count++;
    }
    file.close();

    if (text[0] == '\0')
        strcpy(text, "File is empty");
}

const char* previewer::preview()
{
    return text;
}