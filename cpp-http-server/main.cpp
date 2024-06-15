#include <iostream>
#include "httplib.h"
#include "handlers.h"

int main() {
    // Step 1: Create an instance of the Server
    httplib::Server svr;

    // Step 2: Define a route handler function
    svr.Get("/", GET_root);
    svr.Get("/index.html", GET_handler);
    svr.Get("/style.css", GET_handler);

    // Step 3: Start the server
    svr.listen("localhost", 8080);

    std::cout << "Server started and listening on port 8080..." << std::endl;

    return 0;
}
