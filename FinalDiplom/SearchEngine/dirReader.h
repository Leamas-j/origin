#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdexcept>

class DirReader
{
private:
  std::vector<std::string> files_;
  std::string extensions_;

public:
  DirReader(const std::string& extensions, const std::string& dirName);
  void set_files(const std::string& dirName);
  std::vector<std::string> get_files();
};
