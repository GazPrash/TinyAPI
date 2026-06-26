# TinyAPI - Rest API Framework for C++

> [!WARNING]
> TinyAPI is currently under heavy development and workflows may change in the future. This project is mainly a hobby project and was supposed to be a no-dependency/hackable library and hence if you are planning to use it in production I'd encourage you to do so with caution. Check out [Ongoing Improvements](#ongoing-improvements) section to keep an eye on current development priorities.

TinyAPI is a minimalistic C++ library that allows you to build lightweight REST APIs. Designed to be a bare-bones framework and easily hackable for quickly setting up HTTP Servers or API Clients exactly how you want them to be. Setting up a server is straightforward and user-friendly, allowing you to define the logic for your API endpoints, similar to modern web frameworks like Flask. No third party libraries were used to develop this API framework! (supported on Linux and macOS)

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

// for the complete example, checkout: /example/example_app1.cpp
std::tuple<std::string, std::string> home(RequestContext ctx) {
  // you can access the exact endpoint inside your defined method using the
  // 'ctx.url_endpoint' variable
  std::string response = "Greetings User! Welcome to TinyAPI.";
  return {response, "text/html"};
}

int main(int argc, char const *argv[]) {
  std::string localhost = "127.0.0.1";
  size_t timeout = 1450000; // 14.5s
  int port = argv[1] ? std::stoi(argv[1]) : 8000;
  TinyAPI *new_api = new TinyAPI(port, 8192, 5, localhost, timeout);
  if (new_api->initialize_server() == 1) {
    return 1;
  }

  // Easy Routing
  new_api->getMethods["/"] = HomePage;
  new_api->getMethods["/home"] = HomePage;
  new_api->getMethods["/about"] = AboutPage;
  new_api->getMethods["/gato"] = gatoImage;
  new_api->getMethods["/data"] = getData;
  new_api->getMethods["/login"] = loginPage;

  // Supports live realoding ;) (no recompilation needed for the backend)
  new_api->getMethods["/index.css"] = indexCSS;
  new_api->getMethods["/reset.css"] = resetCSS;
  new_api->getMethods["/showcase"] = showcasePage;
  new_api->getMethods["/showcase.js"] = serveShowcaseJS;
  new_api->getMethods["/showcase.css"] = serveShowcaseCSS;

  new_api->postMethods["/login"] = userLogin;

  new_api->enable_listener();

  delete new_api;
  return 0;
}
```

3. **Build and run!**:

- Make sure you have a C++ compiler (like `g++` or `clang++`) and `CMAKE` (minimum version 3.5) installed.
  - 3.1 Create a build directory and configure/run CMake, followed by `make` to compile the static library:

```bash
mkdir -p build
cd build
cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=OFF
make
```

- Linking the static library:
  - 3.2 Link the generated `libTinyApi.a` static library when compiling your `<your_web_app_name>.cpp` file as follows:

```bash
g++ -std=c++17 <your_web_app_name>.cpp -o <your_web_app_name> -Iinclude -L build/ -lTinyApi
```

- Run the Demo/Example on Mac or Linux:
  - 3.3 Alternatively, you can use the automated script `buildexample.sh` to compile the library and the example app.
  - First, make sure the script has execution permissions and run it:
    ```bash
    chmod +x buildexample.sh
    ./buildexample.sh
    ```
  - Start the example server by specifying a port number (default is 8000 if omitted):
    ```bash
    ./example_app1 8080
    ```
  - You can test the running server in another terminal by running:
    ```bash
    curl -i http://localhost:8080/home
    ```
  - You can customize routes or data by editing the `example/example_app1.cpp` file.


## Contributions

Contributions are welcome! If you'd like to contribute to TinyAPI, please follow these steps:

1. **Fork the repository on GitHub**.
2. **Clone your fork locally**.
3. **Create a new branch for your changes**.
4. **Commit your changes and push to your fork**.
5. **Create a pull request on the main repository**.

## <a id="ongoing-improvements"></a> Ongoing Improvements

I'm actively working on making TinyAPI even better. The next big step is to setup basic functionalities such as POST requests and database support. Furthermore, a multi-threading support for enhanced performance and concurrency is also on the listr. Stay tuned for more features! 
