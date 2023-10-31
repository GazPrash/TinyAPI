#ifndef TINYAPI_H
#define TINYAPI_H

#include "server_utils.h"
#include<iostream>
#include<string>
#include<vector>
#include<ctime>
#include<sstream>
#include<map>
#include<fstream>
#include<tuple>

#ifdef __WIN32__
// on windows systems
# include <winsock2.h>  // Link with -lws2_32
#else
# include <sys/socket.h>
#endif


class TinyAPI{
  private:
    const int port;
    const int buffer_sz;
    std::string ip;
    // std::vector<SOCKET*> online_clients;
  public:
    WSADATA WSAData;
    u_int ssocket; // socket file descriptor of the HTTP server
    struct sockaddr_in ssocket_info;
    int maxRequestHandles;
    std::string HttpHeaderFormat;
    int active_client;
    ServerUtils ServerUtils;

    // float server_wait_time;
    TinyAPI(int port, int buffer_sz, int maxConnections, std::string server_ip);
    ~TinyAPI();
    int initialize_server(bool bind_default = true);
    void HttpRequestHandler(std::tuple<std::string, std::string>(*connector_f)(std::string));
    int SendHttpResponse(u_int client, std::string response, std::string response_format);
    // std::string mapStringify()
};

#endif