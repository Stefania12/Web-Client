#include "includes.h"
#include <string>
#include "InputParser.h"
#include "RequestMaker.h"
#include "buffer.h"

#ifndef CLIENT_H
#define CLIENT_H

// Implements the client's behaviour.
class Client
{
    public:
    // Returns unique instance of Client.
    static Client* get_instance();
    
    ~Client();
    // Manages a command: reads it, offers input prompts if it is the case,
    // sends HTTP request to server, waits for answer, prints it and extracts
    // cookie/jwt when it is the case.
    void manage_command(std::string &command);

    
    private:
    // Unique instance of class.
    static Client* instance;
    // Server info needed when opening connection.
    sockaddr_in server;
    std::string host_name;
    int sockfd;

    // Cookie and jwt info. These are unknown values when set to "".
    std::string cookie;
    std::string jwt;

    // Initializes client's host info.
    Client();
    // Opens a connection to the server. Returns true on success
    // and false otherwise.
    bool open_connection();

    // Functions that send/receive a message to/from the server.
    // They are slightly modified versions of the functions from the lab.
    bool send_to_server(const char* message);
    bool receive_from_server(std::string &s);

    // Extracts the status code from the message.
    int extract_status(std::string message);
    // Extracts and saves the cookie value from the message.
    void extract_cookie(std::string message);
    // Extracts and saves the token value from the message.
    void extract_token(std::string message);
    
    // Functions that return the appropiate message (for the server)
    // for each command type.
    std::string get_register();
    std::string get_login();
    std::string get_logout();
    std::string get_enter_library();
    std::string get_get_books();
    std::string get_get_book();
    std::string get_add_book();
    std::string get_delete_book();
};

#endif