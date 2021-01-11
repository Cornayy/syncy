#include <iostream>
#include <cstdlib>
#include <string>
#include <asio.hpp>
#include "Header/Server/Server.h"

int main()
{
    // Report memory leaks in output tab.
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	while(true)
	{
        try
        {
            const Server server{ Server::PORT, "dir" };
            server.listen();
        }
        catch (const std::exception& ex)
        {
            std::cerr << "server: " << ex.what() << Server::LF;
            return EXIT_FAILURE;
        }
	}
	
    return EXIT_SUCCESS;
}
