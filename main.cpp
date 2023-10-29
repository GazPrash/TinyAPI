#include<bits/stdc++.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "include/tinyapi.h"
#include "include/helper.h"

using namespace std;

const std::string GATO_IMG_PATH = "images/gato.png";


std::string readImageFile(const std::string& filename) {
  std::ifstream file(filename, std::ios::binary);
  if (!file) {
      throw std::runtime_error("Failed to open the image file");
  }
  std::ostringstream ss;
  ss << file.rdbuf();
  return ss.str();
}

std::tuple<std::string, bool> StdResponse(){
  std::map<std::string, std::string> responseMap;
  responseMap["Greet"] = "Welcome Home!";
  auto response = Helper::MapToString(responseMap);
  auto responseTup = std::make_tuple(response, false);
  return responseTup;
}

// route = /home
std::tuple<std::string, bool> StandardHPResponse(){
  std::map<std::string, std::string> responseMap;
  responseMap["Greet"] = "Welcome Home!";
  auto response = Helper::MapToString(responseMap);
  auto responseTup = std::make_tuple(response, false);
  return responseTup;
}
// route = /info
std::tuple<std::string, bool> AboutInfo(){
  std::map<std::string, std::string> responseMap;
  responseMap["Author"] = "Arthur";
  responseMap["Created"] = "2020";
  responseMap["Github"] = "https://github.com/"; 
  auto response = Helper::MapToString(responseMap);
  auto responseTup = std::make_tuple(response, false);
  return responseTup;

}

std::tuple<std::string, bool> gatoImage(){
  std::string imgContent = readImageFile(GATO_IMG_PATH);
  auto responseTup = std::make_tuple(imgContent, true);
  return responseTup;
  // std::map<std::string, std::string> responseMap;
  // responseMap["File"] = GATO_IMG_PATH;
  // return responseMap;
}

std::tuple<std::string, bool> connector(std::string endpoint){
  cout << endpoint << endl;
  if (endpoint == "/home") return StandardHPResponse();
  else if (endpoint == "/info") return AboutInfo();
  else if (endpoint == "/gato"){
    return gatoImage();
  }

  std::string err404 = "404 Not Found!";
  return std::make_tuple(err404, false);
  // std::tuple<std::map<std::string, std::string>, bool> responseTup;
}
// FOR TESTING ONLY!!!
TinyAPIHttpServer* server_ref;
void signal_handler(int signal){
  if (signal == SIGINT){
    delete server_ref;
    exit(0);
  }
}

int main(){
  std::signal(SIGINT, signal_handler);
  std::string localhost = "127.0.0.1";
  TinyAPIHttpServer *server = new TinyAPIHttpServer(8000, 1024, 5, localhost);

  server_ref = server; // For testing only!!!

  if (server->initialize_server() == 1){
    return 1;
  }
  server->AwaitHTTPRequest(&connector);
  return 0;
}

// Compile as follows (Link with winsock2 / Windows only):
// g++ -Iinclude/tinyapi.h -o main_win.exe main.cpp -lws2_32