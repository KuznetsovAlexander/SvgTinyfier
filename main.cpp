#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <windows.h>

#include "SvgTinyfier.h"

std::vector<std::string> getAllSvgs(const std::string& folder)
{
  std::vector<std::string> names;
  std::string search_path = folder + "/*.*";
  WIN32_FIND_DATA fd;
  HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
  if (hFind != INVALID_HANDLE_VALUE) {
    do {
      if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
        std::string filename = fd.cFileName;
        size_t dotPos = filename.find_last_of('.');
        std::string extension = filename.substr(dotPos);
        if (extension == ".svg") {
          names.push_back(fd.cFileName);
        }
      }
    } while (::FindNextFile(hFind, &fd));
    ::FindClose(hFind);
  }
  return names;
}

void tinyfyFile(const std::string& filename)
{
  size_t dotPos = filename.find_last_of('.');
  std::string extension = filename.substr(dotPos);
  std::string nameWithoutExtension = filename.substr(0, dotPos);
  std::string newFilename = nameWithoutExtension + "_tiny" + extension;

  std::ifstream file(filename, std::ios::in);
  std::string fileContent((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
  std::string tinyfiedContent = SvgTinyfier::tinyfy(fileContent);
  
  std::ofstream newFile(newFilename, std::ios::out);
  newFile << tinyfiedContent;
}

int main(int argc, char** argv)
{
  if (argc < 2) {
    std::cout << "Usage: SvgTinyfier.exe FOLDER_WITH_SVGs" << std::endl;
  }

  std::string folder = argv[1];
  std::vector<std::string> svgFiles = getAllSvgs(folder);
  for (auto f : svgFiles) {
    tinyfyFile(folder + "/" + f);
  }

  return 0;
}
