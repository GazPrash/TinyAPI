#include "response_handler.h"
#include "helper.h"
#include <string>
#include <sys/socket.h>

// Must be used when response status is not an error code | 200OK
int HTTPResponseHandler ::HTTPResponseStandard(const int client,
                                               const std::string response,
                                               std::string response_format,
                                               int status_code) {

  std::string httpResponseCode = "HTTP/1.1 200 OK\n";
  std::string httpResponse = "";
  httpResponse += httpResponseCode;
  /*std::string httpResponse = "HTTP/1.1 200 OK\n";*/
  httpResponse += Helper::gerCurrentDate();
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

int HTTPResponseHandler::HTTPResponseError(const int client, int status_code) {
  switch (status_code) {
  // WORK IN PROGRESS
  case 400:
    std::string httpErrorMsg = "HTTP/1.1 400 Bad Request\r\n";
    break;
  }
  return 1;
}
