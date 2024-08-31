#include <curl/curl.h>
#include <gtest/gtest.h>
#include <memory>
#include <thread>
#include <unistd.h>

#include "helper.h"
#include "tinyapi.h"

// route = /home
static std::tuple<std::string, std::string> HomePage() {
  std::map<std::string, std::string> responseMap;
  responseMap["Greet"] = "Welcome Home!";
  auto response = Helper::MapToString(responseMap);
  auto responseTup = std::make_tuple(response, "text/html");
  return responseTup;
}

// connector
static std::tuple<std::string, std::string> connector(std::string endpoint) {
  if (endpoint == "/home")
    return HomePage();

  std::string err404 = "404 - Page Not Found!";
  return std::make_tuple(err404, "text/html");
}

class FooServer {
public:
  std::string local_host = "127.0.0.1";
  bool status_Running = false;
  TinyAPI *new_api;

  int init_server();
  void start_server();
};

class FooTest : public testing::Test {
protected:
  FooServer m_serverObj;
  std::unique_ptr<std::thread> m_server_thread;
};

int FooServer::init_server() {
  new_api = new TinyAPI(8000, 1024, 5, local_host, 2000, TinyAPI::HOST_OS::WIN);
  return new_api->initialize_server();
}

void FooServer::start_server() {
  status_Running = true;
  new_api->HttpRequestHandler(&connector);
}

TEST_F(FooTest, fooTest) {
  ASSERT_EQ(m_serverObj.init_server(), 0);
  // launch server in a different thread
  m_server_thread =
      std::make_unique<std::thread>(&FooServer::start_server, &m_serverObj);
  while (!m_serverObj.status_Running) {
    // stay still
  }
  // forward a GET request to the server
  CURL *curl;
  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:8000/home");
    CURLcode res = curl_easy_perform(curl);
    ASSERT_EQ(res, CURLE_OK);
    curl_easy_cleanup(curl);
  } else {
    FAIL();
  }
  // wait for server timeout
  m_server_thread->join();
}
