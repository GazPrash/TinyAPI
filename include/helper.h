#ifndef HELPER_H
#define HELPER_H

#include<iostream>
#include<string>
#include<ctime>
#include<csignal>
#include<cstdlib>
#include<fstream>
#include<sstream>
#include<map>
#include<unordered_map>


namespace Helper{
  std::string MapToString(const std::map<std::string, std::string> dataMap){
    std::ostringstream map_string;
    map_string << "{";

    for (auto it = dataMap.begin(); it != dataMap.end(); ++it) {
        if (it != dataMap.begin()) {
            map_string << ", ";
        }
        map_string << "\"" << it->first << "\": \"" << it->second << "\"";
    }
    map_string << "}";
    return map_string.str();
  }

  std::string jsonToString(const std::string filepath){
    std::string jsonFilePath = "path_to_your_json_file.json";
    std::ifstream jsonFile(filepath);
    if (!jsonFile.is_open()) {
        std::cerr << "Failed to open the JSON file." << std::endl;
        return "";
    }
    std::string jsonString(
      (std::istreambuf_iterator<char>(jsonFile)), std::istreambuf_iterator<char>()
    );
    std::cout << "JSON content as a string:\n" << jsonString << std::endl;
    return jsonString;
  }
};

#endif // HELPER_H