#pragma once
#include <string>
#include <vector>

namespace cache {

enum class CommandType : uint8_t {
    GET = 1,
    SET = 2,
    DEL = 3,
    UNKNOWN = 255
};

struct Request {
    CommandType type;
    std::string key;
    std::string value;
};

struct Response {
    bool success;
    std::string value;
    std::string message;
};

class Protocol {
public:
    static std::string encode_request(const Request& req);
    static Request decode_request(const std::string& data);

    static std::string encode_response(const Response& res);
    static Response decode_response(const std::string& data);
};

} // namespace cache