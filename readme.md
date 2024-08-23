# TinyAPI - Rest API Framework for C++

TinyAPI is a minimalistic C++ library that allows you to build lightweight REST APIs. With TinyAPI, you can easily create and handle endpoints for sending JSON, text data, and even images. It's designed to be straightforward and user-friendly, allowing you to define the logic for your API endpoints, similar to modern web frameworks like Flask. No third party libraries were used to develop this API framework!

## Features

- **Lightweight and Efficient**: TinyAPI is designed for performance and efficiency.

- **Easy Setup**: Getting started with TinyAPI is simple, thanks to its clean and intuitive design.

- **Flexible Routing**: Define your API endpoints and handle them with custom logic.

- **Support for Various Data Types**: Send and receive JSON, text data, audio and images.

## How to Use

1. **Clone the Repository**: Clone this repository to your local machine using:
```bash
git clone https://github.com/GazPrash/TinyAPI.git
```

2. **Setting up a new API**:

- Create a .cpp file and in the driver function Instantiate the TinyAPI class in your driver function and start listening for HTTP requests!
```cpp
// Include the tinyapi.h header at the top
#include "include/tinyapi.h"

int main(){
  // Quickly setting up a minimal application
  std::string localhost = "127.0.0.1";
  TinyAPI *new_api = new TinyAPI(8000, 1024, 5, localhost, TinyAPI::HOST_OS::WIN);
  if (new_api->initialize_server() == 1){
    return 1;
  }
  new_api->HttpRequestHandler(&connector);
  return 0;
}
```

3. **Routing**:

- You can use meaningful URLs to help clients visiting your application. Just define the ```connector``` function in your code to handle different URL endpoints.

```cpp

std::tuple<std::string, std::string> connector(std::string endpoint){
/**
 * Handle all the necessary endpoints at one place!
 *
 * @param endpoint Requested endpoint by the user
 * @return tuple<response, response_format> response(actual data) and format(text/html or image/png etc)
 */
  if (endpoint == "/home") return HomePage();
  else if (endpoint == "/about") return AboutPage();
  else if (endpoint == "/gato") return gatoImage();

  // You must ensure that this function returns from all of its execution paths
  // so that no compilation error or undefined behaviour may happen.
  // Create a custom 404 Message in case the user requests an unknown endpoint 
  std::string err404 = "404 - Page Not Found!";
  return std::make_tuple(err404, "text/html");
}

```
Now all there left to do is to implement all the different functions for handling different routes such that
each route is binded to a function.

```cpp
// route = /about
std::tuple<std::string, std::string> AboutPage(){
  std::map<std::string, std::string> responseMap;
  responseMap["Made by"] = "Sammy Zane";
  responseMap["Total Downloads"] = "123,000+";
  responseMap["Important links"] = "https://github.com/"; 

  // If you are using a json file, then the JSON object must be converted to std::string format.
  // If you're using std::map then you can use utility functions from helper.h to convert 
  // your map<std::string, std::string> to std::string format.
  // (It is recommended to use Json)
  auto response = Helper::MapToString(responseMap);
  // the return must be a tuple<std::string, std::string> use #include<tuple> header for creating/using tuples.
  auto responseTup = std::make_tuple(response, "text/html");
  return responseTup;
}

```

4. **Compile and run!**:

- Make sure you have a C++ compiler and the Winsock library installed.
- Compile the your program and link it with ```-lws_32``` if you're on windows to use the Winsock library.

```bash
g++ -o example1_app.exe example1.cpp .\src\tinyapi.cpp -Iinclude -lws2_32  
```


## Contributions

Contributions are welcome! If you'd like to contribute to TinyAPI, please follow these steps:

1. **Fork the repository on GitHub**.
2. **Clone your fork locally**.
3. **Create a new branch for your changes**.
4. **Commit your changes and push to your fork**.
5. **Create a pull request on the main repository**.

## Ongoing Improvements

I'm actively working on making TinyAPI even better. THe next big step is to introduce multi-threading support for enhanced performance and concurrency, add encoding support for serving media files, and more.
