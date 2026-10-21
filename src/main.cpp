#include "../include/FilemanagerUI.hpp"
#include <filesystem>
using namespace std;



int main(){
 FilemanagerUI deltaui(fs::current_path());
deltaui.run();

}
