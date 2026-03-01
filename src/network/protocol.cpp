#include "protocol.h"
#include <stdexcept>

namespace cache {

std::string Protocol::encode_request(const Request& req) {
    std::string data;
    data += static_cast<char>(req.type);

    uint16_t key_len = req.key.size();
    data += static_cast<char>(key_len >> 8);
    data += static_cast<char>(key_len & 0xFF);
    data += req.key;

    uint16_t val_len = req.value.size();
    data += static_cast<char>(val_len >> 8);
    data += static_cast<char>(val_len & 0xFF);
    data += req.value;

    return data;
}

Request Protocol::decode_request(const std::string& data) {
    if (data.size() < 5)
        throw std::runtime_error("Request too short");

    Request req;
    req.type = static_cast<CommandType>(data[0]);

    uint16_t key_len = (static_cast<uint8_t>(data[1]) << 8) 
                      | static_cast<uint8_t>(data[2]);
    req.key = data.substr(3, key_len);

    uint16_t val_len = (static_cast<uint8_t>(data[3 + key_len]) << 8) 
                      | static_cast<uint8_t>(data[4 + key_len]);
    req.value = data.substr(5 + key_len, val_len);

    return req;
}

std::string Protocol::encode_response(const Response& res) {
    std::string data;
    data += static_cast<char>(res.success ? 1 : 0);

    uint16_t val_len = res.value.size();
    data += static_cast<char>(val_len >> 8);
    data += static_cast<char>(val_len & 0xFF);
    data += res.value;

    uint16_t msg_len = res.message.size();
    data += static_cast<char>(msg_len >> 8);
    data += static_cast<char>(msg_len & 0xFF);
    data += res.message;

    return data;
}

Response Protocol::decode_response(const std::string& data) {
    if (data.size() < 5)
        throw std::runtime_error("Response too short");

    Response res;
    res.success = data[0] == 1;

    uint16_t val_len = (static_cast<uint8_t>(data[1]) << 8) 
                      | static_cast<uint8_t>(data[2]);
    res.value = data.substr(3, val_len);

    uint16_t msg_len = (static_cast<uint8_t>(data[3 + val_len]) << 8) 
                      | static_cast<uint8_t>(data[4 + val_len]);
    res.message = data.substr(5 + val_len, msg_len);

    return res;
}

} // namespace cache