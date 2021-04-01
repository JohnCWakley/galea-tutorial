#pragma once

#include <string>
#include <vector>

namespace ve
{
    class Pipeline
    {
    public:
        Pipeline(const std::string &vertFilepath, const std::string &fragFilepath);
        ~Pipeline();

    private:
        static std::vector<char> readFile(const std::string &filepath);

        void createGraphicsPipeline(const std::string &vertFilepath, const std::string &fragFilepath);
    };
}
