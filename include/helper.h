#ifndef HELPER_H
#define HELPER_H

#include <csignal>
#include <cstdlib>
#include <ctime>
#include <map>
#include <string>

namespace Helper {
std::string MapToString(const std::map<std::string, std::string> dataMap);
std::string jsonToString(const std::string filepath);
}; // namespace Helper

#endif // HELPER_H
