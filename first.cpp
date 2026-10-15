#include<iostream>
#include<filesystem>
#include<cstring>
#include<fstream>

using namespace std;
namespace fs = filesystem;

class FileManager
{
    fs::path currentPath;
    public:
    FileManager()
    {
        currentPath=fs::current_path();
    }
    void listFiles()
    {
        cout<<"\ncontents of: "<<currentPath<<endl;
        try
        {
            for(const auto&entry:fs::directory_iterator(currentPath))
            {
                if(entry.is_directory())
                cout<<"[DIR]";
                else
                cout<<"[FILE]";
                cout<<entry.path().filename().string()<<endl;
            }
        }
        catch(const fs::filesystem_error& e)
        {
            cout<<"Error: "<<e.what()<<endl;
        }
        
    }
    void changeDir()
    {
        string folder;
        cout<<"Enter dirsctory path: ";
        getline(cin, folder);
        fs::path newPath(folder);
        try
        {
            if(fs::is_directory(newPath))
            {
                currentPath=fs::canonical(newPath);
                cout<<"Directory changed successfully"<<endl;
            }
        }
        catch(const fs::filesystem_error& e)
        {
            cout<<"Error: "<<e.what()<<endl;
        }
        
    }
    void createFile()
    {
        string filename;
        cout<<"Eneter file name: ";
        getline(cin, filename);
        if(filename.empty())
        {
            cout<<"File name can not be empty"<<endl;
            return;
        }
        fs::path filePath=currentPath/filename;

    try
    {
        if(fs::exists(filePath))
        {
            cout<<"A file or folder with that name is already exists"<<endl;
            return;
        }
        ofstream file(filePath);
        if(file)
        cout<<"File created successfully"<<endl;
        else
        cout<<"Could not create file"<<endl;
    }
    catch(const fs::filesystem_error& e)
    {
        cout<<"Error: "<<e.what()<<endl;
    }
    }

    void createFolder()
    {
        string folder;
        cout<<"Enter folder name: ";
        getline(cin, folder);
        if(folder.empty())
        {
            cout<<"folder name can not be empty"<<endl;
            return;
        }
        try
        {
            if(fs::create_directory(currentPath/folder))
            {
                cout<<"Folder created successfully."<<endl;
            }
            else{
                cout<<"Folder already exists or can nor be created."<<endl;
            }
        }
        catch(const fs::filesystem_error& e)
        {
            cout<<"Error: "<<e.what()<<endl;
        }
        
    }

    void goToParentDir()
    {
        fs::path parentPath=currentPath.parent_path();

        if(parentPath!=currentPath && !parentPath.empty())
        {
            currentPath=parentPath;
            cout<<"Moved to parent directory"<<endl;
        }
        else{
                cout<<"Already at top level of directory"<<endl;
            }
    }

    void renameItem()
    {
        string oldName, newName;
        cout<<"Enter current file/folder name: ";
        getline(cin, oldName);
        cout<<"Enter new name: ";
        getline(cin, newName);
        if(oldName.empty()||newName.empty())
        {
            cout<<"File name can not be empty"<<endl;
            return;
        }
        fs::path oldPath=currentPath/oldName;
        fs::path newPath=currentPath/newName;

        try
        {
            if(!fs::exists(oldPath))
            {
                cout<<"File or folder does not exists"<<endl;
                return;
            }
            if(fs::exists(newPath))
            {
                cout<<"An item with the new name already exists"<<endl;
                return;
            }
            fs::rename(oldPath,newPath);
            cout<<"Renamed successfully"<<endl;
        }
        catch(const fs::filesystem_error& e)
        {
            cout<<"Rename failed: "<<e.what()<<endl;
        }
        
    }

    void copyFile()
    {
        string sourceName,destinationName;
        cout<<"Enter source file path: ";
        getline(cin, sourceName);
        cout<<"Enter destination file path: ";
        getline(cin, destinationName);

        if(sourceName.empty() || destinationName.empty())
        {
            cout<<"File names can not be empty"<<endl;
            return;
        }
        fs::path sourcePath(sourceName);
        fs::path destinationPath(destinationName);
        if(sourcePath.is_relative())
        sourcePath=currentPath/sourcePath;

        if(destinationPath.is_relative())
        destinationPath=currentPath/destinationPath;

        try
        {
            if(!fs::exists(sourcePath))
            {
                cout<<"Source file does not exists."<<endl;
                return;
            }
            if(!fs::is_regular_file(sourcePath))
            {
                cout<<"Source is not regular file"<<endl;
                return;
            }
            if(fs::exists(destinationPath))
            {
                cout<<"Destination already exists."<<endl;
            }
            if(fs::copy_file(sourcePath, destinationPath))
            {
                cout<<"File copied successfully."<<endl;
            }
            else{
                cout<<"File could not be copied."<<endl;
            }
        }
        catch(const fs::filesystem_error& e)
        {
                cout<<"Copy failed: "<<e.what()<<endl;
        }
        
    }

    void moveFile()
    {
        string sourceName, destinationName;
        cout<<"Enter source file path: ";
        getline(cin, sourceName);
        cout<<"Enter destination file path: ";
        getline(cin, destinationName);

        if(sourceName.empty() ||destinationName.empty())
        {
            cout<<"Path can not be empty."<<endl;
            return;
        }
        fs::path sourcePath(sourceName);
        fs::path destinationPath(destinationName);

        if(sourcePath.is_relative())
        sourcePath=currentPath/sourcePath;
        if(destinationPath.is_relative())
        destinationPath=currentPath/destinationPath;

        try
        {
            if(!fs::exists(sourcePath)||!fs::is_regular_file(sourcePath))
            {
                cout<<"Source file does not exists or file is not regular"<<endl;
                return;
            }
            if(fs::exists(destinationPath))
            {
                cout<<"Destination already exists."<<endl;
                return;
            }
            if(!fs::is_directory(destinationPath.parent_path()))
            {
                cout<<"Destination directory does not exists."<<endl;
            }
            fs::rename(sourcePath,destinationPath);
            cout<<"File moved successfully"<<endl;
        }
        catch(const fs::filesystem_error& e)
        {
            cout<<"Move failed: "<<e.what()<<endl;
        }
        
    }

   

    void run()
    {
        int choice;
        while(1)
        {
        cout<<"!!File Manager!! YOOOOOOOO !!"<<endl;
        cout<<"Current directory: "<<currentPath<<endl;
        cout<<"1. List files and folders\n2. Change directory\n3. Create Folder\n4. Create File\n5. Go to parent directory\n6. Rename file/folder\n7. Copy file\n8. Move file\n9. Exit\n";
        cout<<"Enter your choise: ";
        if(!(cin>>choice))
        {
            cout<<"Invalid Input."<<endl;
            break;
        }
        cin.ignore(10000,'\n');
        switch(choice)
        {
            case 1:
            listFiles();
            break;

            case 2:
            changeDir();
            break;

            case 3:
            createFolder();
            break;

            case 4:
            createFile();
            break;

            case 5:
            goToParentDir();
            break;

            case 6:
            renameItem();
            break;

            case 7:
            copyFile();
            break;

            case 8:
            moveFile();
            break;

            case 9:
            cout<<"Closing file mnager"<<endl;
            return;
            
            default:
            cout<<"Invalid choice"<<endl;
        }
        }

    }
};

int main()
{
    FileManager fm;
    fm.run();
    return 0;
}