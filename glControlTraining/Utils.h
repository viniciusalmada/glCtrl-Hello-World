#pragma once
#include <string>
#include <vector>

class Utils
{
  static std::vector<std::string> split(std::string s, std::string delimiter);

public:
              static std::string read_file(const std::string& filepath);

  static void write_file(const std::string& filepath, const std::string& content);

  static std::string get_textures_directory(const std::string& executable_path);
};

