#include <filesystem>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/event.hpp>
#include <string>
#include "Filemanager.hpp"
class FilemanagerUI{
    protected:
        Filemanager deltafm;
        std::string statusmsg;
        enum class Mode { Browsing, Typing, Confirming };
        enum class Action { None, CreateFile, CreateFolder, Rename};
        std::string inputtext;
        Mode mode;
        Action pendingaction;



    public:

    FilemanagerUI(const fs::path&);
    void run();

    private:
        ftxui::Element buildscreen();
        ftxui::Element buildlist();
        bool onkey(ftxui::Event event);
        bool handletype(ftxui::Event event);
        void setstatus(const std::string& msg);
        void finishtype();
};
