#include "Research.hpp"

#include "../MazeGenerator/MazeGenerator.hpp"
#include "../Utils/Operators.hpp"
#include "../Utils/Logger.hpp"

#define RESULT_FILE_NAME "result.csv"

namespace research
{

using namespace tests;

Tester Research::preapre()
{
    auto tester = Tester::initialize();
    LOG("Preparing testcases");

//    tester.add(Testcase{"Dummy test 1", TestConfig{RESULT_FILE_NAME, 1, true},
//                                        MazeConfig{{10, 10}, {0, 2}, {9, 2}}});

//    tester.add(Testcase{"Dummy test 2", TestConfig{RESULT_FILE_NAME, 1, true},
//                                        MazeConfig{{20, 20}, {6, 0}, {19, 18}}});

//    tester.add(Testcase{"Dummy test 3", TestConfig{RESULT_FILE_NAME, 1, true},
//                                        MazeConfig{{50, 50}, {39, 0}, {49, 18}}});

//    tester.add(Testcase{"Dummy test 4", TestConfig{RESULT_FILE_NAME, 10, false},
//                                        MazeConfig{{100, 100}, {39, 0}, {0, 98}}});

    tester.add(Testcase{"Dummy test 5", TestConfig{RESULT_FILE_NAME, 5, false},
                                        MazeConfig{{500, 500}, {250, 0}, {250, 499}}});

//    tester.add(Testcase{"Dummy test 6", TestConfig{RESULT_FILE_NAME, 1, true},
//                                        MazeConfig{{1000, 1000}, {1, 0}, {998, 999}}});

//    tester.add(Testcase{"Dummy test 6", TestConfig{RESULT_FILE_NAME, 1, false},
//                                        MazeConfig{{5000, 5000}, {1, 0}, {4998, 4999}}});

    LOG("Preapred", tester.testcases(), "testcases");
    return tester;
}

int Research::run(int, char**)
{
    return preapre().run();
}

}  // namespace research
