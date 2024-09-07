// Compile :
// g++ example_testing.cpp -o testing_app -Iinclude -L build/ -lTinyApi

#include "../include/helper.h"
#include "../include/tinyapi.h"
#include <cstddef>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <tuple>

// You can quickly define a function like this to convert images or any binary
// data into a string format.
std::string readImageFile(const std::string &filename) {
  std::ifstream file(filename, std::ios::binary);
  if (!file) {
    throw std::runtime_error("Failed to open the image file");
  }
  std::ostringstream ss;
  ss << file.rdbuf();
  return ss.str();
}

// route = /home
std::tuple<std::string, std::string> HomePage(std::string url_endpoint) {
  // you can access the exact endpoint inside your defined method using the
  // url_endpoint variable
  std::map<std::string, std::string> responseMap;
  responseMap["Greet"] = "Welcome Home!";
  auto response = Helper::MapToString(responseMap);
  auto responseTup = std::make_tuple(response, "text/html");
  return responseTup;
}

// route = /about
std::tuple<std::string, std::string> AboutPage(std::string url_endpoint) {
  std::map<std::string, std::string> responseMap;
  responseMap["Made by"] = "Sammy Zane";
  responseMap["Total Downloads"] = "123,000+";
  responseMap["Important links"] = "https://github.com/";
  auto response = Helper::MapToString(responseMap);
  auto responseTup = std::make_tuple(response, "text/html");
  return responseTup;
}

std::tuple<std::string, std::string> gatoImage(std::string url_endpoint) {
  const std::string GATO_IMG_PATH = "images/gato.png";
  std::string imgContent = readImageFile(GATO_IMG_PATH);
  auto responseTup = std::make_tuple(imgContent, "image/png");
  return responseTup;
}

std::tuple<std::string, std::string> getData(std::string url_endpoint) {
  const std::string dataPath = "test/data/testdata.json";
  auto response = Helper::jsonToString(dataPath);
  auto responseTup = std::make_tuple(response, "text/html");
  return responseTup;
}

int main() {
  // Quickly setting up a HTTP Rest Api at device's localhost
  std::string localhost = "127.0.0.1";
  size_t timeout = 1450000; // 14.5s
  TinyAPI *new_api =
      new TinyAPI(8000, 1024, 5, localhost, timeout, TinyAPI::HOST_OS::LINUX);
  if (new_api->initialize_server() == 1) {
    return 1;
  }

  // Easy Routing
  new_api->getMethods["/home"] = HomePage;
  new_api->getMethods["/about"] = AboutPage;
  new_api->getMethods["/gato"] = gatoImage;
  new_api->getMethods["/data"] = getData;

  // Start the server
  new_api->enable_listener();
  return 0;
}
