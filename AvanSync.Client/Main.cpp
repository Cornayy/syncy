#include <iostream>
#include <cstdlib>
#include <asio.hpp>
#include "Header/Client/Client.h"

int main()
{
    // Report memory leaks in output tab.
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
    try {
        const Client client{"localhost", "3000"};
        client.listen();
    }
    catch (const std::exception& ex) {
        std::cerr << "client: " << ex.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

