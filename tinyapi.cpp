#include "tinyapi.h"
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>

TinyAPI ::TinyAPI(int port, int buffer_sz, int maxConnections,
                  std::string server_ip, HOST_OS os)
    : port(port), buffer_sz(buffer_sz) {
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

void TinyAPI ::HttpRequestHandler(
    std::tuple<std::string, std::string> (*connector_f)(std::string)) {
  /**
   * This method can be used to establish connection with the Http server.
   *
   * @param None N/A
   * @return 0 if socket is connection is established successfully else 1
   */
  u_int client;
  int client_addr_len;
  struct sockaddr_in client_addr;

  if (ssocket < 0) {
    perror("Socket Not initialized.");
    return;
  }
  // listen(ssocket, maxRequestHandles);
  if (listen(ssocket, SOMAXCONN) < 0) {
    // std::cout << WSAGetLastError() << std::endl;
    perror("Listen failed...Aborting.\n");
    return;
    // return "";
  }
  std::cout << "Server is now open for connection...[PORT:" << port << "]\n";

  // std:: cout << "Connection Established. Waiting for incoming requests.\n";

  // TODO : Add a server timeout instead of infiinite while loop
  char requestBuffer[buffer_sz];
  while (1) {
    /*client = accept(ssocket, (struct sockaddr *)&client_addr,
     * &client_addr_len);*/
    socklen_t client_addr_len = sizeof(client_addr);
    client = accept(ssocket, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client < 0) {
      perror("Couldn't establish connection with the client.");
      // return "";
    }
    // std:: cout << "New Connection Established. Waiting for incoming
    // requests.\n";
    int bytesRead = recv(client, requestBuffer, sizeof(requestBuffer), 0);
    if (bytesRead > 0) {
      // Convert received data to a string
      std::string httpRequest(requestBuffer, bytesRead);
      // Parse the HTTP request to extract the requested URL
      std::istringstream requestStream(httpRequest);
      std::string requestLine;
      std::getline(requestStream, requestLine);
      // Extract the URL from the request line
      std::istringstream requestLineStream(requestLine);
      std::string method, url_endpoint, http_version;
      requestLineStream >> method >> url_endpoint >> http_version;
      std::cout << "New GET Request! - " << url_endpoint << "\n";
      std::tuple<std::string, std::string> responseTup =
          connector_f(url_endpoint);
      std::string response = std::get<0>(responseTup);
      std::string response_format = std::get<1>(responseTup);
      SendHttpResponse(client, response, response_format);
      memset(requestBuffer, 0, sizeof(requestBuffer));
      // delete[] requestBuffer;
    }
  }
  // const std::string std_reply = "This is a standard reply.";
}

int TinyAPI ::SendHttpResponse(u_int client, std::string response,
                               std::string response_format) {
  std::string httpResponse = "HTTP/1.1 200 OK\n";
  httpResponse += serverUtils.getCurDate();
  // httpResponse += "Last-Modified: Mon, 23 Oct 2023 14:40:37 GMT\n";
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
