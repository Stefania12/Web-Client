#include "RequestMaker.h"

std::string RequestMaker::make_post_request(std::string host, std::string url,
                                            json body_data, std::string cookies,
                                            std::string jwt)
{
    std::string message;
    std::string delimiter = "\r\n";
    std::string body = body_data.dump();
    std::string content_type = "application/json";

    // Add request type and protocol version.
    message = std::string("POST ") + url + std::string(" HTTP/1.1") + delimiter;
    // Add host.
    message += std::string("Host: ") + host + delimiter;
    
    // Add content type and content length.
    message += std::string("Content-Type: ") + content_type + delimiter;
    char data_len_str[50];
    sprintf(data_len_str, "%d", (int) body.size());
    message += std::string("Content-Length: ") + std::string(data_len_str)
            + delimiter;

    // Add cookie if available.
    if (cookies.size() > 0)
        message += std::string("Cookie: ") + cookies + delimiter;

    // Add jwt if available.
    if (jwt.size() > 0)
        message += std::string("Authorization: Bearer ") + jwt + delimiter;

    // Add payload.
    message += delimiter + body;

    return message;
}

std::string RequestMaker::make_get_request(std::string host, std::string url,
                                        std::string cookies, std::string jwt)
{
    std::string message;
    std::string delimiter = "\r\n";
    
    // Add request type and protocol version.
    message = std::string("GET ") + url + std::string(" HTTP/1.1") + delimiter;
    // Add host.
    message += std::string("Host: ") + host + delimiter;

    // Add cookie if available.
    if (cookies.size() > 0)
        message += std::string("Cookie: ") + cookies + delimiter;
    
    // Add jwt if available.
    if (jwt.size() > 0)
        message += std::string("Authorization: Bearer ") + jwt + delimiter;

    message += delimiter;

    return message;
}

std::string RequestMaker::make_delete_request(std::string host, std::string url,
                                            std::string cookies, std::string jwt)
{
    std::string message;
    std::string delimiter = "\r\n";
    
    // Add request type and protocol version.
    message = std::string("DELETE ") + url + std::string(" HTTP/1.1")
            + delimiter;
    // Add host.
    message += std::string("Host: ") + host + delimiter;

    // Add cookie if available.
    if (cookies.size() > 0)
        message += std::string("Cookie: ") + cookies + delimiter;
    
    // Add jwt if available.
    if (jwt.size() > 0)
        message += std::string("Authorization: Bearer ") + jwt + delimiter;

    message += delimiter;

    return message;
}