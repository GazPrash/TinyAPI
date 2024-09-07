
#include <string>

namespace HTTPResponseHandler {

// WORK IN PROGRESS
int HTTPResponseStandard(const int client, const std::string response,
                         std::string response_format, int status_code);
int HTTPResponseError(const int client, int status_code);

} // namespace HTTPResponseHandler
