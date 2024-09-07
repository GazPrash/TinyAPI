#include "tinyapi.h"
#include "request_parser.h"
#include <bits/types/struct_timeval.h>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <ostream>
/*#include <sstream>*/
#include <string>
#include <sys/socket.h>
#include <sys/time.h>
#include <tuple>
#include <unistd.h>

TinyAPI ::TinyAPI(int port, int buffer_sz, int maxConnections,
                  std::string server_ip, size_t server_timeout, HOST_OS os)
    : port(port), buffer_sz(buffer_sz), server_timeout(server_timeout) {
  maxRequestHandles = maxConnections;
  ip = server_ip;
  current_os = os;
}

TinyAPI ::~TinyAPI() {
  // write code for closing the main server socket and other cleanup
  std::cout << "Server Closing...\n";
  close(ssocket);
  /*if (current_os == HOST_OS::WIN) {*/
  /*  closesocket(ssocket);*/
  /*  WSACleanup();*/
  /*  std::cout << "Winsock Cleanup Initiated.\n";*/
  /*}*/
}

int TinyAPI ::initialize_server(bool bind_default) {
  /**
   * For initializing the winsock2 library required for using sockets on Windows
   * machines and other server protocols. Creates the main socket for the Http
   * Server. Required process for initialization.
   *
   * @param bind_default Keep this true if you wish to automatically bind the
   * server socket after creation.
   * @return 0 if socket is created successfully else 1
   */
  int iResult;
  if (current_os == HOST_OS::WIN) {
    // Initializing the Winsock Library.
    /*iResult = WSAStartup(MAKEWORD(2, 2), &WSAData);*/
    /*if (iResult != 0) {*/
    /*  perror("WSAStartup Failed. Aborting server initialization.\n");*/
    /*  return 1;*/
    /*}*/
    /*std::cout << "Winsock Initiated.\n";*/
  }
  // No initialization required for Linux's socket library

  ssocket = socket(AF_INET, SOCK_STREAM, 0);
  if (ssocket < 0) {
    return 1;
  }
  if (!bind_default)
    return 0;

  ssocket_info.sin_addr.s_addr = inet_addr(ip.c_str());
  ssocket_info.sin_family = AF_INET;
  ssocket_info.sin_port = htons(port);

  if (bind(ssocket, (const struct sockaddr *)&ssocket_info,
           sizeof(ssocket_info)) < 0) {
    // std::cout<<WSAGetLastError();
    perror("Failed to bind server socket");
    return 1;
  }
  return 0;
}

void TinyAPI ::enable_listener() {
  /**
   * This method can be used to establish connection with the Http server.
   *
   * @param None N/A
   * @return 0 if socket is connection is established successfully else 1
   */
  u_int client;
  int clint_addr_len;
  struct sockaddr_in client_addr;

  if (ssocket < 0) {
    perror("Socket Not initialized.");
    return;
  }
  if (listen(ssocket, SOMAXCONN) < 0) {
    perror("Listen failed...Aborting.\n");
    return;
  }

  struct timeval serv_timeout;
  size_t server_timeout_sec = server_timeout / 1000; // ms to seconds
  serv_timeout.tv_sec = server_timeout_sec;
  serv_timeout.tv_usec = 500000; // microseconds
  // Limiting the Server Socket to the timeout provided by
  // the user Controlled Timeouts
  setsockopt(ssocket, SOL_SOCKET, SO_RCVTIMEO, (const char *)&serv_timeout,
             sizeof(serv_timeout));

  time_t server_start_time = time(NULL);
  std::cout << "Server is now open for connection...[PORT:" << port << "]\n";

  // TODO : Add a server timeout instead of infiinite while loop
  char requestBuffer[buffer_sz];
  while (1) {
    time_t current_time = time(NULL);
    if (difftime(current_time, server_start_time) >= server_timeout_sec) {
      std::cerr << "Server Timed out! (ET : " << server_timeout << " ms) \n";
      break;
    }
    socklen_t client_addr_len = sizeof(client_addr);
    client = accept(ssocket, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client < 0) {
      std::cerr << "Couldn't establish connection with the client. \n";
    }
    // requests.\n";
    int bytesRead = recv(client, requestBuffer, sizeof(requestBuffer), 0);
    if (bytesRead < 0) {
      continue;
    }
    std::tuple<std::string, int> parsedRequest =
        HTTPParser::parseBytes(bytesRead, requestBuffer, buffer_sz);
    if (std::get<1>(parsedRequest) != 200) {
      // handle http error reporting
      continue;
    }
    std::string httpRequest = std::get<0>(parsedRequest);
    std::string method, url_endpoint, http_version;
    std::tuple<std::string, int> requestInfo =
        HTTPParser::HTTPR11(httpRequest, method, url_endpoint, http_version);

    if (std::get<1>(requestInfo) != 200) {
      // handle http error reporting
      std::cout << "Current Method is : " << method << std::endl;
      std::cout << "HTTP version is : " << http_version << std::endl;
      std::cerr << "Unsupported HTTP method" << std::endl;
      SendHttpResponse(client, "405 - Method Not Allowed", "text/plain",
                       "HTTP/1.1 : 405 Method Not Allowed\r\n");
      continue;
    }

    auto getmethod = getMethods[url_endpoint];
    if (!getmethod) {
      /*send a response to the user that this route/endpoint is being requested
       * by the user but not covered by the web api*/
      std::cout << "Route cannot be served : " << url_endpoint << std::endl;
      continue;
    }
    std::tuple<std::string, std::string> responseTup = getmethod(url_endpoint);
    std::string response = std::get<0>(responseTup);
    std::string response_format = std::get<1>(responseTup);
    SendHttpResponse(client, response, response_format);
    memset(requestBuffer, 0, sizeof(requestBuffer));
  }
}

int TinyAPI ::SendHttpResponse(u_int client, std::string response,
                               std::string response_format,
                               std::string httpResponseCode) {

  std::string httpResponse = "";
  httpResponse += httpResponseCode;
  /*std::string httpResponse = "HTTP/1.1 200 OK\n";*/
  httpResponse += serverUtils.getCurDate();
  httpResponse += "Content-Type: " + response_format + "\n";
  httpResponse += "Content-Length:" + std::to_string(response.size()) + "\n";
  httpResponse += "Accept-Ranges: bytes\n";
  httpResponse += "Connection: close\n";
  httpResponse += "\n";
  httpResponse += response;

  const char *httpResponseCStr = httpResponse.c_str();
  if (send(client, httpResponseCStr, httpResponse.size(), 0) < 0) {
    return 1;
  }
  return 0;
}
