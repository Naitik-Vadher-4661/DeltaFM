#pragma once
#include"Filesystemitem.hpp"


class Directoryitem:public Filesystemitem{
  protected:
    int childcount;
  public:
      Directoryitem(fs::path);
      std::string gettype() const ;
      std::string getdisplaytext() const;
      int getcc();
      ~Directoryitem();
};
