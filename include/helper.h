#ifndef HELPER_H
#define HELPER_H

#include <csignal>
#include <cstdlib>
#include <ctime>
#include <unordered_map>
#include <string>

namespace Helper {
std::string MapToString(const std::unordered_map<std::string, std::string>& dataMap);
std::string jsonToString(const std::string& filepath);
std::string getCurrentDate();
}; // namespace Helper

#endif // HELPER_H
