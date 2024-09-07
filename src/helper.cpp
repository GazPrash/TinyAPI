#include "helper.h"
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

std::string
Helper::MapToString(const std::map<std::string, std::string> dataMap) {
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

std::string Helper::jsonToString(const std::string filepath) {
  std::ifstream jsonFile(filepath);
  if (!jsonFile.is_open()) {
    std::cerr << "Failed to open the JSON file." << std::endl;
    return "";
  }
  std::ostringstream json_string;
  json_string << jsonFile.rdbuf();
  return json_string.str();
}

std::string Helper::gerCurrentDate() {
  const time_t now = time(nullptr);
  struct tm *timeInfo;
  timeInfo = gmtime(&now);
  char buffer[80];
  strftime(buffer, sizeof(buffer), "Date: %a, %d %b %Y %H:%M:%S GMT\r\n",
           timeInfo);
  std::string dateToday = buffer;
  return dateToday;
}
