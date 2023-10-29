#include<string>
#include<ctime>

class ServerUtils{
public:
  static std::string getCurDate(){
  const time_t now = time(nullptr);
  struct tm* timeInfo;
  timeInfo = gmtime(&now);
  char buffer[80];
  strftime(buffer, sizeof(buffer), "Date: %a, %d %b %Y %H:%M:%S GMT\r\n", timeInfo);
  std::string dateToday = buffer;
  return dateToday;
  }


};