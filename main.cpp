#include "includes.h"
#include  "Client.h"
#include "RequestMaker.h"

// Closes the client.
void close_everything()
{
    delete Client::get_instance();
}

int main()
{
    while(true)
    {
        // Read command.
        std::string command;
        getline(std::cin, command);

        // If exit then close program.
        if (command.compare("exit") == 0)
        {
            close_everything();
            return 0;
        }

        // Manage the command.
        Client::get_instance()->manage_command(command);
    }

    return 0;
}