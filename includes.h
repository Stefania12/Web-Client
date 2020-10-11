#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>

#ifndef INCLUDES_H
#define INCLUDES_H

#include "json.hpp"
using json = nlohmann::json;
#define HOST "ec2-3-8-116-10.eu-west-2.compute.amazonaws.com"
#define REGISTER_URL "/api/v1/tema/auth/register"
#define LOGIN_URL "/api/v1/tema/auth/login"
#define LIBRARY_ACCESS_URL "/api/v1/tema/library/access"
#define BOOKS_URL "/api/v1/tema/library/books"
#define LOGOUT_URL "/api/v1/tema/auth/logout"

#endif
