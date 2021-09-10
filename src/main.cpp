#include "app.hpp"
#include "logger.hpp"

#include <cstdlib>
#include <iostream>
#include <stdexcept>

int main()
{
    log_info("starting demo");
    
    ve::App app{};

    try
    {
        app.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}