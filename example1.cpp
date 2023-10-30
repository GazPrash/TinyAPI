#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "include/tinyapi.h"
#include "include/helper.h"


// You can quickly define a function like this to convert images or any binary data into a string format.
std::string readImageFile(const std::string& filename) {
  std::ifstream file(filename, std::ios::binary);
  if (!file) {
      throw std::runtime_error("Failed to open the image file");
  }
  std::ostringstream ss;
  ss << file.rdbuf();
  return ss.str();
}

// route = /home
std::tuple<std::string, std::string> HomePage(){
  std::map<std::string, std::string> responseMap;
  responseMap["Greet"] = "Welcome Home!";
  auto response = Helper::MapToString(responseMap);
  auto responseTup = std::make_tuple(response, "text/html");
  return responseTup;
}

// route = /info
std::tuple<std::string, std::string> AboutPage(){
  std::map<std::string, std::string> responseMap;
  responseMap["Author"] = "Arthur";
  responseMap["Created"] = "2020";
  responseMap["Github"] = "https://github.com/"; 
  auto response = Helper::MapToString(responseMap);
  auto responseTup = std::make_tuple(response, "text/html");
  return responseTup;

}

std::tuple<std::string, std::string> gatoImage(){
  const std::string GATO_IMG_PATH = "images/gato.png";
  std::string imgContent = readImageFile(GATO_IMG_PATH);
  auto responseTup = std::make_tuple(imgContent, "image/png");
  return responseTup;
}

std::tuple<std::string, std::string> connector(std::string endpoint){
  if (endpoint == "/home") return HomePage();
  else if (endpoint == "/about") return AboutPage();
  else if (endpoint == "/gato") return gatoImage();
  // Create a custom 404 Message in case the user requests an unknown endpoint 
  // You must ensure that this function returns from all of its execution paths
  // so that no compilation error or undefined behaviour may happen.
  std::string err404 = "404 - Page Not Found!";
  return std::make_tuple(err404, "text/html");
}

int main(){
  // Quickly setting up an HTTP server at device's localhost 
  std::string localhost = "127.0.0.1";
  TinyAPIHttpServer *server = new TinyAPIHttpServer(8000, 1024, 5, localhost);
  if (server->initialize_server() == 1){
    return 1;
  }
  // this method activates a listening cycle so that a server can 
  // recieve and respond to multiple client requests.
  // You must create a "connector" function that returns a string tuple
  // The connector function must have all the logic regarding how a given request must be handled
  // you can create different functions for handling different requests based on different routes
  // so that you can tell TinyAPI what URL should trigger this function!
  // Connector function must return a string tuple such that :
  // First element is : text/json/binary in std::string format
  // And the second element should be : format of the data i.e text/html or image/png or image/jpeg 
  server->HttpRequestHandler(&connector);
  return 0;
}

// Compile as follows (Link with winsock2 / Windows only):
// g++ -o example1_app.exe example1.cpp .\src\tinyapi.cpp -Iinclude -lws2_32  
// And then run the executable file!