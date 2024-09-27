# TinyAPI - Rest API Framework for C++

[!Warning] TinAPI is currently under heavy development and workflows may change in the future. This project is mainly a hobby project and was supposed to be a no-dependency/hackable library and hence if you are planning to use it in production I'd encourage you to do so with caution. Check out [Ongoing Improvements](#ongoing-improvements) section to keep an eye on current development priorities.

TinyAPI is a minimalistic C++ library that allows you to build lightweight REST APIs. Designed to be a bare-bones framework and easily hackable for quickly setting up HTTP Servers or API Clients exactly how you want them to be. Setting up a server is straightforward and user-friendly, allowing you to define the logic for your API endpoints, similar to modern web frameworks like Flask. No third party libraries were used to develop this API framework! (currently only supported on Linux)

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

2. **Quickly setting up a new API**:

- Create a `.cpp` file and in the driver function Instantiate the `TinyAPI` class in your driver function and start listening for HTTP requests!
```cpp
// Include the tinyapi.h header at the top
#include "include/tinyapi.h"

std::tuple<std::string, std::string> home(std::string url_endpoint) {
  // you can access the exact endpoint inside your defined method using the
  // 'url_endpoint' variable
  std::string response = "Greetings User! Welcome to TinyAPI.";
  return {response, "text/html"};
}

int main() {
  // Quickly setting up a basic (HTTP/1.1) REST Api at device's localhost
  std::string localhost = "127.0.0.1";
  size_t timeout = 1450000; // 14.5s
  TinyAPI *new_api =
      new TinyAPI(8000, 1024, 5, localhost, timeout, TinyAPI::HOST_OS::LINUX);
  if (new_api->initialize_server() == 1) {
    return 1;
  }

  // Easy Routing
  new_api->getMethods["/home"] = home;

  // Start the server
  new_api->enable_listener();
  return 0;
}
```

3. **Build and run!**:

- Make sure you have a C++ compiler and `CMAKE` (minimum version 3.2) is installed.
  - 4.1 Create a build directory and run the `cmake` command, followed by the make command to finalize the build.

```bash
mkdir -p build
cd build
cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=OFF
make
```

- Linking the static library
  - 4.2 Link the generated `libTinyApi.a` static library when compiling your `<your_web_app_name>.cpp` file as follows:

```bash
g++ <your_web_app_name>.cpp -o <your_web_app_name> -Iinclude -L build/ -lTinyApi
```

- Run the Demo/Example
  - 4.3 Alternatively, you can run the `buildexample.sh` file to quickly build the static library and setup a test example web server (`example_app1.o`) on the go. You can add your routes and data by updating the file `example_app1.cpp` that can be found in the `example` directory.


## Contributions

Contributions are welcome! If you'd like to contribute to TinyAPI, please follow these steps:

1. **Fork the repository on GitHub**.
2. **Clone your fork locally**.
3. **Create a new branch for your changes**.
4. **Commit your changes and push to your fork**.
5. **Create a pull request on the main repository**.

## <a id="ongoing-improvements"></a> Ongoing Improvements

I'm actively working on making TinyAPI even better. The next big step is to introduce multi-threading support for enhanced performance and concurrency, add encoding support for serving media files (currently Images are supported), and more.
