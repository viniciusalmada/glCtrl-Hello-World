#include "Utils.h"

#include <fstream>
#include <iostream>

std::vector<std::string> Utils::split(std::string s, const std::string delimiter)
{
  size_t pos = 0;
  std::vector<std::string> splits;
  while ((pos = s.find(delimiter)) != std::string::npos)
  {
    std::string token = s.substr(0, pos);
    splits.push_back(token);
    s.erase(0, pos + delimiter.length());
  }
  splits.push_back(s);
  return splits;
}

std::string Utils::read_file(const std::string& filepath)
{
  std::ifstream in_file;
  in_file.open(filepath);
  if (!in_file)
  {
    std::cerr << "Unable to open file";
    return {};
  }
  std::string line;
  std::string file_content;
  while (in_file >> line)
  {
    file_content.append(line);
    file_content.append("\n");
  }
  in_file.close();

  return file_content;
}

void Utils::write_file(const std::string& filepath, const std::string& content)
{
  std::ofstream out_file;
  out_file.open(filepath);
  if (!out_file)
  {
    std::cerr << "Unable to open file";
    return;
  }
  out_file << content;
  out_file.close();
}

std::string Utils::get_textures_directory(const std::string& executable_path)
{
  auto splits = split(executable_path, "\\");
  splits.pop_back();
  splits.pop_back();
  std::string texture_dir;
  for (std::string dir : splits)
  {
    texture_dir.append(dir).append("\\");
  }
  texture_dir.append("textures");
  return texture_dir;
}
