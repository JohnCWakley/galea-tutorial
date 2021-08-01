#include "galea/app.hpp"

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <spdlog/spdlog.h>

int main()
{
#ifndef NDEBUG
    spdlog::set_level(spdlog::level::debug);
#endif

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