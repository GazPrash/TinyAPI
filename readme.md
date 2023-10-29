# Tiny API - A C++ API Library

Tiny API is a minimalistic C++ library that allows you to build lightweight REST APIs using the Winsock library. With Tiny API, you can easily create and handle endpoints for sending JSON, text data, and even images. It's designed to be straightforward and user-friendly, allowing you to define the logic for your API endpoints, similar to modern web frameworks like Flask. No third party libraries were used to develop this API framework!

## Features

- **Lightweight and Efficient**: Tiny API is designed for performance and efficiency.

- **Easy Setup**: Getting started with Tiny API is simple, thanks to its clean and intuitive design.

- **Flexible Routing**: Define your API endpoints and handle them with custom logic.

- **Support for Various Data Types**: Send and receive JSON, text data, and even images.

- **Ongoing Improvements**: We are actively working on making Tiny API multi-threaded for better concurrency and responsiveness.

## How to Use

1. **Clone the Repository**: Clone this repository to your local machine using:
```bash
git clone https://github.com/yourusername/tiny-api.git
```

2. **Build and Compile**:

- Make sure you have a C++ compiler and the Winsock library installed.
- Compile the project using your preferred compiler. For example, you can use g++ on Linux or Visual Studio on Windows.

3. **Define Your Endpoints**:

- In your C++ code, define the endpoints you want to handle using Tiny API.

```cpp

std::tuple<std::string, bool> connector(std::string endpoint){
/**
 * Handle all the necessary endpoints at one place!
 *
 * @param endpoint Requested endpoint by the user
 * @return tuple<response, is_binary> response and format of the response
 */
  cout << endpoint << endl;
  if (endpoint == "/home") return HomePage();
  else if (endpoint == "/info") return AboutInfo();
  else if (endpoint == "/pictures/gato"){
    return gatoImage();
  }
  std::string err404 = "404 Not Found!";
  return std::make_tuple(err404, false);
}
```
4. **Start the server!**:

- Execute the Tiny API server to start recieving HTTP requests!
```cpp
  std::string localhost = "127.0.0.1";
  TinyAPIHttpServer *server = new TinyAPIHttpServer(8000, 1024, 5, localhost);
  if (server->initialize_server() == 1){
    return 1;
  }
  server->AwaitHTTPRequest(&connector);

```

## Contributions

Contributions are welcome! If you'd like to contribute to Tiny API, please follow these steps:

1. **Fork the repository on GitHub**.
2. **Clone your fork locally**.
3. **Create a new branch for your changes**.
4. **Commit your changes and push to your fork**.
5. **Create a pull request on the main repository**.

## Ongoing Improvements

I'm actively working on making Tiny API even better. THe next big step is to introduce multi-threading support for enhanced performance and concurrency. At the moment, I've implemented the HTTP Server using Winsock library, which is designed for socket programming on Windows devices. In the future, I will try to create a version of the library that's compatible with Linux, making it accessible to a broader user base.
