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


class TinyAPIHttpServer{
  private:
    const int port;
    const int buffer_sz;
    std::string ip;
    // std::vector<SOCKET*> online_clients;
  public:
    WSADATA WSAData;
    u_int ssocket; // socket file descriptor
    struct sockaddr_in ssocket_info;
    int maxRequestHandles;
    std::string HttpHeaderFormat;
    int active_client;
    ServerUtils ServerUtils;

    // float server_wait_time;
    TinyAPIHttpServer(int port, int buffer_sz, int maxConnections, std::string server_ip);
    ~TinyAPIHttpServer();
    int initialize_server(bool bind_default = true);
    void AwaitHTTPRequest(std::tuple<std::string, bool>(*connector_f)(std::string));
    int SendHTTPResponse(u_int client, std::string response);
    int SendHTTPImage(u_int client, std::string filepath);
    int SendHTTPImage_Testing(u_int client, std::string response);
    // std::string mapStringify()
};

#endif