#include <string>

namespace HTTPParser {
std::tuple<std::string, int>
parseBytes(const int bytesRead, char *requestBuffer, const int buffer_sz);
std::tuple<std::string, int> HTTPR11(std::string httpRequest,
                                     std::string &method,
                                     std::string &url_endpoint,
                                     std::string &http_version);
} // namespace HTTPParser
