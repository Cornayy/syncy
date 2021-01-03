#include <iostream>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include <asio.hpp>
#include "Header/Server/Server.h"

int main() {

	while(true)
	{
        try
        {
            const Server server{ Server::PORT };
            server.listen();
        }
        catch (const std::exception & ex)
        {
            std::cerr << "server: " << ex.what() << Server::LF;
            return EXIT_FAILURE;
        }
	}
	
    return EXIT_SUCCESS;
}
