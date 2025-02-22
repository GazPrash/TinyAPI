#include "tinyapi.h"
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>

RequestContext RequestHandler::HTTPR11(const int bytesRead, char *requestBuffer,
                                       const int buffer_sz) {
  RequestContext ctx;

  if (bytesRead >= buffer_sz) {
    std::cerr << "413 - Payload too large" << std::endl;
    /*SendHttpResponse(client, "Payload Exceeded", "text/plain",*/
    /*                 "HTTP/1.1 413 Payload Too Large\r\n");*/
    ctx.message = "Payload Exceeded";
    ctx.status_code = STATUS_CODE::PAYLOAD_TOO_LARGE;
    return ctx;
  } else {
    requestBuffer[bytesRead] = '\0';
  }
  // Convert received data to a string
  std::string httpRequest(requestBuffer, bytesRead);
  ctx.request_body = httpRequest;

  std::string method, url_endpoint, http_version;
  std::istringstream requestStream(ctx.request_body);
  std::string requestLine;
  if (!std::getline(requestStream, requestLine)) {
    std::cerr << "Invalid request" << std::endl;
    /*SendHttpResponse(client, "400 - Bad Request", "text/plain",*/
    /*                 "HTTP/1.1 400 Bad Request\r\n");*/
    int error_status_code = 400;

    ctx.request_body = "Invalid request";
    ctx.status_code = STATUS_CODE::BAD_REQUEST;
    return ctx;
  }
  // Extract the URL from the request line
  std::istringstream requestLineStream(requestLine);
  requestLineStream >> method >> url_endpoint >> http_version;

  if (method == "GET") {
    ctx.http_method = HTTP_METHOD::GET;
    ctx.status_code = STATUS_CODE::OK;
  } else if (method == "POST") {
    ctx.http_method = HTTP_METHOD::POST;
    ctx.status_code = STATUS_CODE::OK;
  } else {
    ctx.http_method = HTTP_METHOD::UNSUPPORTED;
    ctx.status_code = STATUS_CODE::METHOD_NOT_ALLOWED;
  }

  ctx.url_endpoint = url_endpoint;
  ctx.http_version = http_version;

  return ctx;
}
