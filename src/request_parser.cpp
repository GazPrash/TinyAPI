#include "request_parser.h"
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <tuple>

std::tuple<std::string, int>
/*Returns <ParsedBytes, Status Code> (Empty string if parsing fails, along with
   the satus code) */
HTTPParser::parseBytes(const int bytesRead, char *requestBuffer,
                       const int buffer_sz) {
  // Null termination for avoiding offerflow (bytesRead <= 4096). This
  // should almost never ever happen but just ensuring that requestBuffer is
  // null terminated.
  if (bytesRead >= buffer_sz) {
    std::cerr << "413 - Payload too large" << std::endl;
    /*SendHttpResponse(client, "Payload Exceeded", "text/plain",*/
    /*                 "HTTP/1.1 413 Payload Too Large\r\n");*/
    int error_status_code = 413;
    return std::make_tuple("", error_status_code);
  } else {
    requestBuffer[bytesRead] = '\0';
  }
  // Convert received data to a string
  std::string httpRequest(requestBuffer, bytesRead);
  std::cout << httpRequest << std::endl;
  return std::make_tuple(httpRequest, 200);
}

std::tuple<std::string, int> HTTPParser::HTTPR11(std::string httpRequest,
                                                 std::string &method,
                                                 std::string &url_endpoint,
                                                 std::string &http_version) {
  std::istringstream requestStream(httpRequest);
  std::string requestLine;
  if (!std::getline(requestStream, requestLine)) {
    std::cerr << "Invalid request" << std::endl;
    /*SendHttpResponse(client, "400 - Bad Request", "text/plain",*/
    /*                 "HTTP/1.1 400 Bad Request\r\n");*/
    int error_status_code = 400;
    return std::make_tuple("", error_status_code);
  }
  // Extract the URL from the request line
  std::istringstream requestLineStream(requestLine);
  requestLineStream >> method >> url_endpoint >> http_version;

  if (method == "GET" || method == "POST") {
    // TODO : Add Logging

    std::cout << "HTTPR11 \n";
    std::cout << "New Request! - " << url_endpoint
              << " Version : " << http_version << "\n";
    std::cout << "FIne til now" << std::endl;
    return std::make_tuple(url_endpoint, 200);
  }

  // Method Not Allowed
  int error_status_code = 405;
  return std::make_tuple(url_endpoint, error_status_code);
}
