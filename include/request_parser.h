#include <string>

namespace HTTPParser {
std::tuple<std::string, std::string>
parseBytes(const int bytesRead, char *requestBuffer, const int buffer_sz);
std::tuple<std::string, std::string> HTTPR11(std::string httpRequest,
                                             std::string &method,
                                             std::string &url_endpoint,
                                             std::string &http_version);
} // namespace HTTPParser
