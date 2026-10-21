#include "../include/previewer.hpp"
#include<fstream>
#include<cstring>

previewer::previewer()
{     
    loadpreview();      
}

void previewer::loadpreview()
{
    text[0]='\0';
    fs::path path=items[selectedIndex]->getpath();
    std::error_code ec;

    if(fs::is_directory(path,ec))
    {
        strcpy(text, "This is a directory");
        return;
    }

    std::string ext=path.extension().string();
    if(ext==".jpg" || ext==".jpeg" || ext==".png" || ext==".gif" || ext==".webp" || ext==".mp3" || ext==".mp4" || ext==".mkv")
    {
        strcpy(text, "Preview not available");
        return;
    }

    std::ifstream file(path);
    if(!file)
    {
        strcpy(text, "Unable to open for preview");
        return;
    }

    char line[100];
    int count=0;                                
    while(count<5 && file.getline(line,100))
    {
        strcat(text,line);
        strcat(text,"\n");
        count++;
    }
    file.close();

    if(text[0]=='\0')
        strcpy(text, "File is empty");
}

const char* previewer::preview()
{
    return text;
}