#include "Testcase.hpp"

#include "../../Utils/Logger.hpp"
#include "../../Maze/MazeApp.hpp"
#include "../../MazeGenerator/MazeGenerator.hpp"

#define SOLVING_METHODS_NUMBER 6


namespace research
{
namespace tests
{

Testcase::Testcase(std::string title,
                  TestConfig tConfig,
                  MazeConfig mConfig)
    : m_title{std::move(title)}
    , m_tConfig{std::move(tConfig)}
    , m_mConfig{std::move(mConfig)}
    , m_argc{0}
    , m_argv{nullptr}
{}

bool Testcase::prepareNthArgs(const unsigned n,
                              const std::string& resultfilename,
                              const std::string& method,
                              const std::string& logfilename,
                              const std::string& isDrawing)
{
    constexpr auto MIN_ARGS_NUMBER{3};
    if (n < MIN_ARGS_NUMBER)
    {
        LOG("Cannot prepare less than", MIN_ARGS_NUMBER, "arguments");
        return false;
    }

    m_argv = new char*[n];

    const char applicationName[] = "MazeApp";
    for (auto i{0u}; i < n; ++i)
    {
        m_argc = i + 1;
        switch (i)
        {
        case 0:
            m_argv[i] = new char[sizeof(applicationName)];
            strcpy_s(m_argv[i], sizeof(applicationName), applicationName);
        break;
        case 1:
            m_argv[i] = new char[resultfilename.size() + 1];
            strcpy_s(m_argv[i], resultfilename.size() + 1, resultfilename.c_str());
        break;
        case 2:
            m_argv[i] = new char[method.size() + 1];
            strcpy_s(m_argv[i], method.size() + 1, method.c_str());
        break;
        case 3:
            m_argv[i] = new char[logfilename.size() + 1];
            strcpy_s(m_argv[i], logfilename.size() + 1, logfilename.c_str());
        break;
        case 4:
            m_argv[i] = new char[isDrawing.size() + 1];
            strcpy_s(m_argv[i], isDrawing.size() + 1, isDrawing.c_str());
        break;
        }
    }
    return true;
}

bool Testcase::prepareArgs(const std::string& filename,
                           const unsigned method)
{
    if (filename.empty())
    {
        LOG("Empty filename");
        return false;
    }
    else if (method > SOLVING_METHODS_NUMBER)
    {
        LOG("There is no ", method, "th method of solving. Only",
            SOLVING_METHODS_NUMBER, "are available");
        return false;
    }

    auto args{3};
    if (not m_tConfig.resultsFileName.empty())
    {
        ++args;
        if (m_tConfig.isDrawingOn)
        {
            ++args;
        }
    }

    return prepareNthArgs(args, filename, std::to_string(method),
                          m_tConfig.resultsFileName,
                          std::to_string(m_tConfig.isDrawingOn));
}

void Testcase::clearArgs()
{
    if (m_argv)
    {
        for (auto i{0u}; i < m_argc; ++i)
        {
            delete [] m_argv[i];
        }
        delete [] m_argv;
    }
    m_argc = 0;
    m_argv = nullptr;
}


bool Testcase::prepareMaze(std::string filename)
{
    return mazegenerator::MazeGenerator(m_mConfig.size.first, m_mConfig.size.second)
            .startAt(m_mConfig.beginPoint)
            .endAt(m_mConfig.endPoint)
            .outputFile(std::move(filename))
            .generate();
}

bool Testcase::run()
{
    LOG("[TESTRUN - START] ", m_title);
    auto result{false};
    auto file{m_mConfig.ownMazeName.empty() ? nextFilename() : m_mConfig.ownMazeName};


    if (not m_mConfig.ownMazeName.empty() or prepareMaze(file))
    {
        for (auto i{1u}; i <= SOLVING_METHODS_NUMBER; ++i)
        {
            if (prepareArgs(file, i))
            {
                for (auto rep{0u}; rep < m_tConfig.repetitionTimes; ++rep)
                {
                    result = (maze::MazeApp{}.run(m_argc, m_argv) == 0);
                    if (not result)
                    {
                        LOG("Mazerunner exited with false result");
                        break;
                    }
                }
                clearArgs();
            }
            else
            {
                LOG("Failed due to preparing args for solving using ", i, "th method");
                break;
            }
        }
    }

    LOG("[TESTRUN - FINISH] ", m_title);
    return result;
}

}  // namespace tests
}  // namespace research
