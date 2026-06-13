#include "dirReader.h"

#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

DirReader::DirReader(const std::string& extensions, const std::string& dirName) : extensions_(extensions)
{
  set_files(dirName);
}

void DirReader::set_files(const std::string& dirName)
{
  std::vector<fs::path> files;
  std::vector<fs::path> dirs;

  for (const auto& entry : fs::directory_iterator(dirName))
  {
    if (fs::is_regular_file(entry.path()))
    {
      files.push_back(entry.path());
    }
    else if (fs::is_directory(entry.path()))
    {
      dirs.push_back(entry.path());
    }
  }

  for (const auto& dir : dirs)
  {    
    set_files(dir.string());
  }

  for (const auto& file : files)
  {
    std::string ext = file.extension().string().erase(0, 1);
    if (ext.size())
    {
      size_t found = extensions_.find(ext);
      if (found != std::string::npos)
      {       
        files_.push_back(file.string());
      }
    }
  }
}
std::vector<std::string> DirReader::get_files()
{
  return files_;
}
