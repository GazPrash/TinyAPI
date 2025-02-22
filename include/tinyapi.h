#ifndef TINYAPI_H
#define TINYAPI_H

#include "request_parser.h"
#include "server_utils.h"
#include <arpa/inet.h>
#include <cstddef>
#include <ctime>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <tuple>
#include <unistd.h>
#include <unordered_map>
#include <vector>

class TinyAPI {
private:
  const int port;
  const int buffer_sz;
  std::string ip;
  const size_t server_timeout;
  // std::vector<SOCKET*> online_clients;
#ifdef __WIN32__
  WSADATA WSAData;
#endif
  u_int ssocket; // socket file descriptor of the HTTP server
  struct sockaddr_in ssocket_info;
  int maxRequestHandles;
  std::string HttpHeaderFormat;
  int active_client;
  ServerUtils serverUtils;
  std::vector<std::string> available_http_methods = {"GET", "POST"};

  // float server_wait_time;
  RequestHandler requestHandler;
  int SendHttpResponse(u_int client, std::string response,
                       std::string response_format,
                       std::string httpResponseCode = "HTTP/1.1 200 OK\n");
  std::string parsePostRequest(std::string);

public:
  TinyAPI(int port, int buffer_sz, int maxConnections, std::string server_ip,
          size_t server_timeout);
  ~TinyAPI();
  std::unordered_map<std::string,
                     std::tuple<std::string, std::string> (*)(std::string)>
      getMethods;
  std::unordered_map<std::string, std::tuple<std::string, std::string> (*)(
                                      std::string, std::string)>
      postMethods;
  int initialize_server(bool bind_default = true);
  void enable_listener();
};

#endif
