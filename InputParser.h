#include "includes.h"

#ifndef INPUTPARSER_H
#define INPUTPARSER_H

// Parses stdin input based on the command type.
class InputParser
{
    public:
    // Parses for register and login commands.
    // Returns the json object.
    static json parse_register_login();
    // Parses for get_book and delete_book.
    // Returns the id as int.
    static int parse_get_book_delete_book();
    // Parses for add_book.
    // Returns the json object.
    static json parse_add_book();


    private:
    // Checks if string is a valid number (unsigned positive).
    static bool is_valid_number(std::string &s);
};

#endif