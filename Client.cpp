#include "Client.h"

Client* Client::instance = nullptr;

Client::Client()
{
    host_name = std::string("ec2-3-8-116-10.eu-west-2.compute.amazonaws.com");

    char* ip_string = inet_ntoa((struct in_addr)*((struct in_addr *)
                        gethostbyname(host_name. c_str())->h_addr_list[0]));
    inet_aton(ip_string, &server.sin_addr);
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
}

Client::~Client()
{
}

Client* Client::get_instance()
{
    if (!instance)
        instance = new Client();
    return instance;
}

bool Client::open_connection()
{
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return false;

    if (connect(sockfd, (const sockaddr*)&server, sizeof(server)) < 0)
        return false;
    return true;
}


bool Client::send_to_server(const char *message)
{
    int bytes, sent = 0;
    int total = strlen(message);

    do
    {
        bytes = write(sockfd, message + sent, total - sent);
        if (bytes < 0)
            return false;

        if (bytes == 0)
            break;

        sent += bytes;
    } while (sent < total);

    return true;
}

bool Client::receive_from_server(std::string &s)
{
    char response[BUFLEN];
    buffer buffer = buffer_init();
    int header_end = 0;
    int content_length = 0;

    do {
        int bytes = read(sockfd, response, BUFLEN);

        if (bytes < 0)
            return false;

        if (bytes == 0) {
            break;
        }

        buffer_add(&buffer, response, (size_t) bytes);
        
        header_end = buffer_find(&buffer, HEADER_TERMINATOR,
                                HEADER_TERMINATOR_SIZE);

        if (header_end >= 0) {
            header_end += HEADER_TERMINATOR_SIZE;
            
            int content_length_start = buffer_find_insensitive(&buffer,
                                        CONTENT_LENGTH, CONTENT_LENGTH_SIZE);
            
            if (content_length_start < 0) {
                continue;           
            }

            content_length_start += CONTENT_LENGTH_SIZE;
            content_length = strtol(buffer.data + content_length_start,
                                    NULL, 10);
            break;
        }
    } while (1);
    size_t total = content_length + (size_t) header_end;
    
    while (buffer.size < total) {
        int bytes = read(sockfd, response, BUFLEN);

        if (bytes < 0)
            return false;

        if (bytes == 0) {
            break;
        }

        buffer_add(&buffer, response, (size_t) bytes);
    }
    buffer_add(&buffer, "", 1);


    if (buffer.data != NULL)
        s = std::string(buffer.data);
    else
        s = std::string();

    return true;
}


void Client::manage_command(std::string &command)
{
    std::string message;

    // Build the message based on the command type.
    if (command.compare("register") == 0)
        message = get_register();

    if (command.compare("login") == 0)
    {
        // If already logged if, refuse a new login command.
        if (cookie.size() > 0)
        {
            std::cout << "You are already logged in! Please log out first.\n";
            return;
        }
        message = get_login();
    }

    if (command.compare("logout") == 0)
        message = get_logout();

    if (command.compare("enter_library") == 0)
        message = get_enter_library();

    if (command.compare("get_books") == 0)
        message = get_get_books();

    if (command.compare("get_book") == 0)
        message = get_get_book();

    if (command.compare("add_book") == 0)
        message = get_add_book();

    if (command.compare("delete_book") == 0)
        message = get_delete_book();


    // If the command is valid, thus the message is not empty.
    if (message.size() > 0)
    {

        // Connect to the server. If it fails, print the error.
        if (!open_connection())
        {
            perror("An error occurred while connecting to server");
            return;
        }

        // Send message. If it fails, print the error.
        if (!send_to_server(message.c_str()))
        {
            perror("An error occurred while sending message to server");
            close(sockfd);
            return;
        }

        // Receive answer. If it fails, print the error.
        if (!receive_from_server(message))
        {
            perror("An error occured while receiving answer from server");
            close(sockfd);
            return;
        }

        // Print answer.
        std::cout << std::endl << message << std::endl << std::endl;

        // If the command was login, then extract cookie from the answer
        // only if the status is OK (command was valid).
        if (command.compare("login") == 0)
        {
            int status = extract_status(message);
            if (status == 200)
                extract_cookie(message);
        }

        // If the command was login, then extract the jwt from the answer
        // only if the status is OK (command was valid).
        if (command.compare("enter_library") == 0)
        {
            int status = extract_status(message);
            if (status == 200)
                extract_token(message);
        }

        // If the command was logout, set the cookie and jwt to "".
        if (command.compare("logout") == 0)
        {
            cookie = std::string();
            jwt = std::string();
        }
    }
    else
    {
        // Invalid command.
        std::cout << "Invalid command.\n";
    }
}

int Client::extract_status(std::string message)
{
    std::string s;
    int idx;

    // Find the second space delimited word and atoi it.
    idx = message.find(' ');
    s = message.substr(idx+1);

    idx = s.find(' ');
    s = s.substr(0, idx);

    return atoi(s.c_str());
}

void Client::extract_cookie(std::string message)
{
    // Find beginning of cookie.
    int idx = message.find("\r\nSet-Cookie: ") + strlen("\r\nSet-Cookie: ");
    // If it exists, then set the cookie field to the appropriate value.
    if (idx >= 0)
    {
        cookie = message.substr(idx);
        idx = cookie.find("\r\n");
        cookie = cookie.substr(0, idx);
    }
}

void Client::extract_token(std::string message)
{
    json j = json::parse(message.substr(message.find('{')).c_str());
    jwt = j["token"].get<std::string>();
}

std::string Client::get_register()
{
    json j = InputParser::parse_register_login();
    return RequestMaker::make_post_request(host_name, REGISTER_URL, j,
                                            std::string(), std::string());
}

std::string Client::get_login()
{
    json j = InputParser::parse_register_login();
    return RequestMaker::make_post_request(host_name, LOGIN_URL, j,
                                            std::string(), std::string());
}

std::string Client::get_logout()
{
    return RequestMaker::make_get_request(host_name, LOGOUT_URL,
                                            cookie, std::string());
}

std::string Client::get_enter_library()
{
    return RequestMaker::make_get_request(host_name, LIBRARY_ACCESS_URL,
                                            cookie, std::string());
}

std::string Client::get_get_books()
{
    return RequestMaker::make_get_request(host_name, BOOKS_URL,
                                            cookie, jwt);
}

std::string Client::get_get_book()
{
    int id = InputParser::parse_get_book_delete_book();
    std::string url = std::string(BOOKS_URL) + std::string("/")
                    + std::to_string(id);
    return RequestMaker::make_get_request(host_name, url, cookie, jwt);
}

std::string Client::get_add_book()
{
    json j = InputParser::parse_add_book();
    return RequestMaker::make_post_request(host_name, BOOKS_URL, j,
                                            cookie, jwt);
}

std::string Client::get_delete_book()
{
    int id = InputParser::parse_get_book_delete_book();
    std::string url = std::string(BOOKS_URL) + std::string("/")
                    + std::to_string(id);
    return RequestMaker::make_delete_request(host_name, url, cookie, jwt);
}