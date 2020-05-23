#pragma once

#include "TestConfig.hpp"

namespace research
{
namespace tests
{

class Testcase
{
public:
    explicit Testcase(std::string title,
                      TestConfig tConfig,
                      MazeConfig mConfig);

    bool run();

private:
    void clearArgs();
    bool prepareArgs(const std::string& filename,
                     const unsigned method);
    bool prepareNthArgs(const unsigned n,
                        const std::string& resultfilename,
                        const std::string& method,
                        const std::string& logfilename,
                        const std::string& isDrawing);

    bool prepareMaze(std::string filename);

    static std::string nextFilename()
    {
        static auto no{0u};
        std::string name{"generated_"};
        name += std::to_string(no++);
        name += ".maze";
        return name;
    }

private:
    std::string m_title;
    TestConfig m_tConfig;
    MazeConfig m_mConfig;
    unsigned m_argc;
    char** m_argv;
};

}  // namespace tests
}  // namespace research
