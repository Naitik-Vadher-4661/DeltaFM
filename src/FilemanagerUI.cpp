#include "../include/FilemanagerUI.hpp"
#include "../include/Exception.hpp"
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>

using namespace ftxui;

FilemanagerUI::FilemanagerUI(const fs::path& startpath)
    : deltafm(startpath),
      statusmsg("Ready"),
      inputtext(""),
      mode(Mode::Browsing),
      pendingaction(Action::CreateFile) {}

void FilemanagerUI::setstatus(const std::string& msg) {
    statusmsg = msg;
}


Element FilemanagerUI::buildlist() {
    Elements rows;
    const auto& items = deltafm.getitems();
    int selected = deltafm.getselected();

    for (int i = 0; i < static_cast<int>(items.size()); i++) {
        Element line = text(" " + items[i]->getdisplaytext());
        if (i == selected) {
            line = line | inverted | focus;
        }
        rows.push_back(line);
    }

    if (rows.empty()) {
        rows.push_back(text(" (empty folder)") | dim);
    }

    return vbox(std::move(rows)) | vscroll_indicator | yframe | flex;
}

Element FilemanagerUI::buildscreen() {
    Element body = vbox({
        text(" " + deltafm.getpath().string()) | bold,
        separator(),
        buildlist(),
        separator(),
        text(" " + statusmsg),
        text(" Up/Down move | Right open | Left up | n file | f folder | r rename | d delete | s sort | h hidden | q quit") | dim,
    }) | border;
    if (mode == Mode::Confirming) {
           const auto& items = deltafm.getitems();
           std::string name = items.empty() ? "" : items[deltafm.getselected()]->getname();

           Element popup = vbox({
               text("Delete \"" + name + "\"?") | bold,
               text(""),
               text("It will be permanently deleted") | color(Color::Red),
               text("and cannot be recovered.") | color(Color::Red),
               separator(),
               text("y = yes, delete    n = no, cancel") | dim,
           }) | border | clear_under | size(WIDTH, GREATER_THAN, 40);

           return dbox({body, popup | center});
       }
    if (mode == Mode::Typing) {
        std::string prompt;
        switch (pendingaction) {
            case Action::None : break;
            case Action::CreateFile:   prompt = "New file name:";   break;
            case Action::CreateFolder: prompt = "New folder name:"; break;
            case Action::Rename:       prompt = "Rename to:";       break;
        }

        Element popup = vbox({
            text(prompt) | bold,
            text(inputtext + "_"),
            text("Enter = confirm, Esc = cancel") | dim,
        }) | border | clear_under | size(WIDTH, GREATER_THAN, 40);

        return dbox({body, popup | center});
    }

    return body;
}

bool FilemanagerUI::onkey(Event event) {
    if (mode == Mode::Typing) {
        return handletype(event);
    }
    if (mode == Mode::Confirming) {
           if (event == Event::Character('y') || event == Event::Character('Y')) {
               const auto& items = deltafm.getitems();
               if (!items.empty()) {
                   std::string name = items[deltafm.getselected()]->getname();
                   try {
                       deltafm.deleteselected();
                       setstatus("Deleted " + name);
                   } catch (const FileException& e) {
                       setstatus(e.what());
                   }
               }
               mode = Mode::Browsing;
               return true;
           }
           if (event == Event::Character('n') || event == Event::Character('N') ||
               event == Event::Escape) {
               mode = Mode::Browsing;
               setstatus("Delete cancelled");
               return true;
           }
           return true;
    }
    try {
        if (event == Event::ArrowUp) {
            deltafm.moveup();
            return true;
        }
        if (event == Event::ArrowDown) {
            deltafm.movedown();
            return true;
        }
        if (event == Event::ArrowLeft) {
            deltafm.gotoparent();
            setstatus("Ready");
            return true;
        }
        if (event == Event::ArrowRight) {
            deltafm.gotochild();
            setstatus("Ready");
            return true;
        }
        if (event == Event::Character('n')) {
            mode = Mode::Typing;
            pendingaction = Action::CreateFile;
            inputtext.clear();

            return true;
        }
        if (event == Event::Character('f')) {
            mode = Mode::Typing;
            pendingaction = Action::CreateFolder;
            inputtext.clear();
            return true;
        }
        if (event == Event::Character('r')) {
            const auto& items = deltafm.getitems();
            if (items.empty()) {
                setstatus("Nothing to rename");
                return true;
            }
            mode = Mode::Typing;
            pendingaction = Action::Rename;
            inputtext = items[deltafm.getselected()]->getname();  // prefill
            return true;
        }
        if (event == Event::Character('d')) {
            const auto& items = deltafm.getitems();
                       if (items.empty()) {
                           setstatus("Nothing to delete");
                           return true;
                       }

                       mode = Mode::Confirming;
                       return true;
        }
        if (event == Event::Character('s')) {
            deltafm.defaultsortitem();
            setstatus("Sorted");
            return true;
        }
        if (event == Event::Character('h')) {
            deltafm.togglehidden();
            setstatus("Toggled hidden files");
            return true;
        }
    } catch (const FileException& e) {
        setstatus(e.what());
        return true;
    }

    return false;
}

bool FilemanagerUI::handletype(Event event) {
    if (event == Event::Escape) {
        mode = Mode::Browsing;
        inputtext.clear();
        setstatus("Cancelled");
        return true;
    }
    if (event == Event::Return) {
        finishtype();
        return true;
    }
    if (event == Event::Backspace) {
        if (!inputtext.empty()) {
            inputtext.pop_back();
        }
        return true;
    }
    if (event.is_character()) {
        inputtext += event.character();
        return true;
    }
    return true;
}

void FilemanagerUI::finishtype() {
    if (inputtext.empty()) {
        setstatus("Name cannot be empty");
        mode = Mode::Browsing;
        return;
    }

    try {
        switch (pendingaction) {
            case Action::CreateFile:
                setstatus("Created file " + inputtext);
                deltafm.createfile(inputtext);
                deltafm.loaddirectory();
                break;
            case Action::CreateFolder:
                setstatus("Created folder " + inputtext);
                deltafm.createfolder(inputtext);
                deltafm.loaddirectory();
                break;
            case Action::Rename:
                 setstatus("Renamed to " + inputtext);
                deltafm.renameselected(inputtext);
                deltafm.loaddirectory();
                break;
            case Action::None : break;
        }
    } catch ( FileException& e) {
        setstatus(e.what());
    }

    mode = Mode::Browsing;
    inputtext.clear();
}


void FilemanagerUI::run() {
    auto screen = ScreenInteractive::Fullscreen();

    auto renderer = Renderer([&] { return buildscreen(); });

    auto app = CatchEvent(renderer, [&](Event event) {

        if (mode == Mode::Browsing && event == Event::Character('q')) {
            screen.Exit();
            return true;
        }
        return onkey(event);
    });

    screen.Loop(app);
}
