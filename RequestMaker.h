#include "includes.h"

#ifndef REQUESTMAKER_H
#define REQUESTMAKER_H

// Builds HTTP requests.
class RequestMaker
{
    public:
    // Builds and returns a GET request.
    // Adds cookie/jwt if it is a non-empty string.
    static std::string make_get_request(std::string host, std::string url,
                                        std::string cookies, std::string jwt);

    // Builds and returns a POST request. Adds a json as payload.
    // Adds cookie/jwt if it is a non-empty string.
    static std::string make_post_request(std::string host, std::string url,
                                        json body_data,
                                        std::string cookies, std::string jwt);

    // Builds and returns a DELETE request.
    // Adds cookie/jwt if it is a non-empty string.
    static std::string make_delete_request(std::string host, std::string url,
                                        std::string cookies, std::string jwt);
};

#endif