# TinyAPI - Rest API Framework for C++

TinyAPI is a minimalistic C++ library that allows you to build lightweight REST APIs. Designed to be a bare-bones framework for quickly setting up HTTP Servers or API Clients. Setting up a server is straightforward and user-friendly, allowing you to define the logic for your API endpoints, similar to modern web frameworks like Flask. No third party libraries were used to develop this API framework! (currently only supported on Linux)

## Features

- **Lightweight and Efficient**: TinyAPI is designed for performance and efficiency.

- **Easily Setup API Clients**: Getting started with TinyAPI is simple, thanks to its clean and intuitive design.

- **Flexible Routing**: Define your API endpoints and handle them with custom logic.

<!-- - **Support for **: Send and receive JSON, audio and images. -->

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

int main() {
  // Quickly setting up an HTTP server at device's localhost
  std::string localhost = "127.0.0.1";
  size_t timeout = 14500; // 14.5s
  TinyAPI *new_api =
      new TinyAPI(8000, 1024, 5, localhost, timeout, TinyAPI::HOST_OS::LINUX);
  /*std::cout << &new_api << std::endl;*/
  if (new_api->initialize_server() == 1) {
    return 1;
  }
  // this method activates a listening cycle so that a server can
  // recieve and respond to multiple client requests.
  // You must create a "connector" function that returns a string tuple
  // The connector function must have all the logic regarding how a given
  // request must be handled you can create different functions for handling
  // different requests based on different routes so that you can tell TinyAPI
  // what URL should trigger this function! Connector function must return a
  // string tuple such that : First element is : text/json/binary in std::string
  // format And the second element should be : format of the data i.e text/html
  // or image/png or image/jpeg
  new_api->HttpRequestHandler(&connector);
  return 0;
}
```

3. **Routing**:

- You can use meaningful URLs to help clients visiting your application. Just define the ```connector``` function in your code to handle different URL endpoints.

```cpp

std::tuple<std::string, std::string> connector(std::string endpoint) {
  if (endpoint == "/home")
    return HomePage();
  else if (endpoint == "/gatowallpaper")
    return gatoWallpaper();
  else if (endpoint == "/clientData")
    return getClientData();

  // Create a custom 404 Message in case the user requests an unknown endpoint
  // You must ensure that this function returns from all of its execution paths
  // so that no compilation error or undefined behaviour may happen.
  std::string err404 = "Page Not Found!";
  return std::make_tuple(err404, "text/html");
}

```
Now all there left to do is to implement all the different functions for handling different routes such that
each route is binded to a function.

```cpp
/route ='/home'
std::tuple<std::string, std::string> HomePage() {
  std::map<std::string, std::string> responseMap;
  responseMap["Greet"] = "Welcome Home!";
  auto response = Helper::MapToString(responseMap);
  auto responseTup = std::make_tuple(response, "text/html");
  return responseTup;
}

// route='/gatowallpaper'
std::tuple<std::string, std::string> gatoWallpaper() {
  const std::string GATO_IMG_PATH = "images/gato.png";
  std::string imgContent = readImageFile(GATO_IMG_PATH);
  auto responseTup = std::make_tuple(imgContent, "image/png");
  return responseTup;
}

// route='/clientData'
std::tuple<std::string, std::string> getClientData() {
  const std::string dataPath = "test/data/testdata.json";
  auto response = Helper::jsonToString(dataPath);
  auto responseTup = std::make_tuple(response, "text/html");
  return responseTup;
}

```

4. **Compile and run!**:

- Make sure you have a C++ compiler and CMAKE (minimum ver 3.2) is installed.

  - 4.1 Create a build directory and run the cmake command, followed by the make command to finalize the build.

```bash
mkdir -p build
cd build
cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=OFF
make
```

  - 4.2 Link the generated `libTinyApi.a` static library when compiling your `<your_web_app_name>.cpp` file as follows:

```bash
g++ <your_web_app_name>.cpp -o <your_web_app_name> -Iinclude -L build/ -lTinyApi
```

  - 4.3 Alternatively, you can run the `buildexample.sh` file to quickly build the static library and setup a test example web server (`example_app1.o`) on the go. You can add your routes and data by updating the file `example_app1.cpp` that can be found in the `example` directory.


## Contributions

Contributions are welcome! If you'd like to contribute to TinyAPI, please follow these steps:

1. **Fork the repository on GitHub**.
2. **Clone your fork locally**.
3. **Create a new branch for your changes**.
4. **Commit your changes and push to your fork**.
5. **Create a pull request on the main repository**.

## Ongoing Improvements

I'm actively working on making TinyAPI even better. The next big step is to introduce multi-threading support for enhanced performance and concurrency, add encoding support for serving media files (currently Images are supported), and more.
