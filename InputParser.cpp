#include "InputParser.h"
#include <string>

json InputParser::parse_register_login()
{
    json j;
    std::string username, password;

    std::cout << "username=";
    getline(std::cin, username);

    while (username.size() == 0 || username.size() > 50)
    {
        std::cout << "Username must be non-empty and up to 50 characters.\n";
        std::cout << "Please try something else.\n";
        std::cout << "username=";
        getline(std::cin, username);
    }

    std::cout << "password=";
    getline(std::cin, password);

    while (password.size() == 0 || password.size() > 50)
    {
        std::cout << "Password must be non-empty and up to 50 characters.\n";
        std::cout << "Please try something else.\n";
        std::cout << "password=";
        getline(std::cin, password);
    }

    j["username"]=username;
    j["password"]=password;
    return j;
}

bool InputParser::is_valid_number(std::string &s)
{
    for (int i = 0; i < (int)s.size(); i++)
        if (s[i] < '0' || s[i] > '9')
            return false;
    
    return s.size() > 0;
}

int InputParser::parse_get_book_delete_book()
{
    std::string id_str;

    std::cout << "id=";
    getline(std::cin, id_str);
    
    // Only accepts a positive number for the id field.
    // Repeats the prompt until a positive number is given.
    while (id_str.size() > 15 || !InputParser::is_valid_number(id_str))
    {
        std::cout << "The field \"id\" must be an unsigned number up to 15 digits.\n";
        std::cout << "Please try again.\n";
        std::cout << "id=";
        getline(std::cin, id_str);
    }

    return atoi(id_str.c_str());
}

json InputParser::parse_add_book()
{
    json j;
    std::string title, author, genre, page_count, publisher;

    std::cout << "title=";
    getline(std::cin, title);

    while (title.size() == 0)
    {
        std::cout << "The field \"title\" must be non-empty.\n";
        std::cout << "Please try again.\n";
        std::cout << "title=";
        getline(std::cin, title);
    }

    std::cout << "author=";
    getline(std::cin, author);

    while (author.size() == 0)
    {
        std::cout << "The field \"author\" must be non-empty.\n";
        std::cout << "Please try again.\n";
        std::cout << "author=";
        getline(std::cin, author);
    }

    std::cout << "genre=";
    getline(std::cin, genre);

    while (genre.size() == 0)
    {
        std::cout << "The field \"genre\" must be non-empty.\n";
        std::cout << "Please try again.\n";
        std::cout << "genre=";
        getline(std::cin, genre);
    }

    std::cout << "publisher=";
    getline(std::cin, publisher);

    while (publisher.size() == 0)
    {
        std::cout << "The field \"publisher\" must be non-empty.\n";
        std::cout << "Please try again.\n";
        std::cout << "publisher=";
        getline(std::cin, publisher);
    }

    std::cout << "page_count=";
    getline(std::cin, page_count);

    // Only accepts a positive number for the page_count field.
    // Repeats the prompt until a positive number is given.
    while (page_count.size() > 15 || !InputParser::is_valid_number(page_count))
    {
        std::cout << "The field \"page_count\" must be an unsigned number up to 15 digits.\n";
        std::cout << "Please try again.\n";
        std::cout << "page_count=";
        getline(std::cin, page_count);
    }


    j["title"] = title;
    j["author"] = author;
    j["genre"] = genre;
    j["publisher"] = publisher;
    j["page_count"] = atoi(page_count.c_str());

    return j;
}