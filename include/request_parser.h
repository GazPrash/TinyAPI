#include <string>
#include <iostream>

enum HTTP_METHOD { GET, POST, PUT, UNSUPPORTED };

enum STATUS_CODE {
  OK = 200,
  BAD_REQUEST = 400,
  PAYLOAD_TOO_LARGE = 413,
  METHOD_NOT_ALLOWED = 405
};

class RequestContext {
public:
  std::string message;
  HTTP_METHOD http_method;
  std::string http_version;
  std::string url_endpoint;
  STATUS_CODE status_code;
  std::string request_body;
  std::string request_headers;
  std::string request_params;

  void log() {
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "| Message: " << message << std::endl;
    std::cout << "| HTTP Method: " << http_method << std::endl;
    std::cout << "| HTTP Version: " << http_version << std::endl;
    std::cout << "| URL Endpoint: " << url_endpoint << std::endl;
    std::cout << "| Status Code: " << status_code << std::endl;
    // std::cout << "| Request Body: " << request_body << std::endl;
    std::cout << "| Request Headers: " << request_headers << std::endl;
    std::cout << "| Request Params: " << request_params << std::endl;
    std::cout << "----------------------------------------" << std::endl;
  }
};

class RequestHandler {
public:
  static RequestContext HTTPR11(const int bytesRead, char *requestBuffer,
                                const int buffer_sz);
};
