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
#include <memory>

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

bool validatePostRequest(const std::string& parsed_request) {
  std::cout << "Parsed Request: " << parsed_request << std::endl;
  std::unordered_map<std::string, std::string> formData;
  std::istringstream stream(parsed_request);
  std::string pair;

  while (std::getline(stream, pair, '&')) {
    size_t pos = pair.find('=');
    if (pos != std::string::npos) {
      std::string key = pair.substr(0, pos);
      std::string value = pair.substr(pos + 1);
      formData[key] = value;
    }
  }

  return (formData["username"] == "admin" &&
          formData["password"] == "password");
}

std::tuple<std::string, std::string> userLogin(const RequestContext& ctx) {
  if (!validatePostRequest(ctx.request_body))
    return std::make_tuple("Invalid Request", "text/html");

  const std::string adminFilePath = "example/static/admin.html";
  std::ifstream file(adminFilePath, std::ios::binary);
  if (!file)
    return std::make_tuple("Failed to open the file", "text/html");
  std::stringstream buffer;
  buffer << file.rdbuf();
  std::string html = buffer.str();
  auto responseTup = std::make_tuple(html, "text/html");
  return responseTup;
}

std::tuple<std::string, std::string> loginPage(const RequestContext& ctx) {
  const std::string filePath = "example/static/login.html";
  std::ifstream file(filePath, std::ios::binary);
  if (!file)
    return std::make_tuple("Failed to open the file", "text/html");
  std::stringstream buffer;
  buffer << file.rdbuf();
  std::string html = buffer.str();
  auto responseTup = std::make_tuple(html, "text/html");
  return responseTup;
}

std::tuple<std::string, std::string> resetCSS(const RequestContext& ctx) {

  const std::string filePath = "example/static/reset.css";
  std::ifstream file(filePath, std::ios::binary);
  if (!file)
    return std::make_tuple("Failed to open the file", "text/html");
  std::stringstream buffer;
  buffer << file.rdbuf();
  std::string html = buffer.str();
  auto responseTup = std::make_tuple(html, "text/css");
  return responseTup;
}

std::tuple<std::string, std::string> indexCSS(const RequestContext& ctx) {

  const std::string filePath = "example/static/index.css";
  std::ifstream file(filePath, std::ios::binary);
  if (!file)
    return std::make_tuple("Failed to open the file", "text/html");
  std::stringstream buffer;
  buffer << file.rdbuf();
  std::string html = buffer.str();
  auto responseTup = std::make_tuple(html, "text/css");
  return responseTup;
}

std::tuple<std::string, std::string> showcasePage(const RequestContext& ctx) {
  const std::string filePath = "example/static/showcase.html";
  std::ifstream file(filePath, std::ios::binary);
  if (!file)
    return std::make_tuple("Failed to open the file", "text/html");
  std::stringstream buffer;
  buffer << file.rdbuf();
  std::string html = buffer.str();
  auto responseTup = std::make_tuple(html, "text/html");
  return responseTup;
}

std::tuple<std::string, std::string> serveShowcaseJS(const RequestContext& ctx) {
  const std::string filePath = "example/static/showcase.js";
  std::ifstream file(filePath, std::ios::binary);
  if (!file)
    return std::make_tuple("Failed to open the file", "text/html");
  std::stringstream buffer;
  buffer << file.rdbuf();
  std::string js = buffer.str();
  auto responseTup = std::make_tuple(js, "application/javascript");
  return responseTup;
}

std::tuple<std::string, std::string> serveShowcaseCSS(const RequestContext& ctx) {
  const std::string filePath = "example/static/showcase.css";
  std::ifstream file(filePath, std::ios::binary);
  if (!file)
    return std::make_tuple("Failed to open the file", "text/html");
  std::stringstream buffer;
  buffer << file.rdbuf();
  std::string css = buffer.str();
  auto responseTup = std::make_tuple(css, "text/css");
  return responseTup;
}


int main(int argc, char const *argv[]) {
  std::string localhost = "127.0.0.1";
  size_t timeout = 1450000; // 14.5s
  int port = argv[1] ? std::stoi(argv[1]) : 8000;
  auto new_api = std::make_unique<TinyAPI>(port, 8192, 5, localhost, timeout);
  if (new_api->initialize_server() == 1) {
    return 1;
  }

  // Easy Routing with Lambdas
  auto homeLambda = [](const RequestContext& ctx) {
    std::unordered_map<std::string, std::string> responseMap;
    responseMap["Greet"] = "Welcome Home!";
    return std::make_tuple(Helper::MapToString(responseMap), "text/html");
  };

  new_api->getMethods["/"] = homeLambda;
  new_api->getMethods["/home"] = homeLambda;

  new_api->getMethods["/gato"] = [](const RequestContext& ctx) {
    return std::make_tuple(readImageFile("images/gato.png"), "image/png");
  };

  new_api->getMethods["/data"] = [](const RequestContext& ctx) {
    return std::make_tuple(Helper::jsonToString("test/data/testdata.json"), "text/html");
  };
  new_api->getMethods["/login"] = loginPage;

  new_api->getMethods["/index.css"] = indexCSS;
  new_api->getMethods["/reset.css"] = resetCSS;
  new_api->getMethods["/showcase"] = showcasePage;
  new_api->getMethods["/showcase.js"] = serveShowcaseJS;
  new_api->getMethods["/showcase.css"] = serveShowcaseCSS;

  new_api->postMethods["/login"] = userLogin;

  new_api->enable_listener();

  return 0;
}
