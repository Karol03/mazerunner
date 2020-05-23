#pragma once

#include <algorithm>
#include <vector>

#include "Tests/Testcase.hpp"

namespace research
{

class Tester
{
private:
    explicit Tester() = default;

public:
    static Tester& initialize()
    {
        static auto tester = Tester{};
        return tester;
    }

    inline Tester& add(tests::Testcase testcase)
    {
        m_testcases.push_back(std::move(testcase));
        return *this;
    }

    inline auto testcases() const
    {
        return m_testcases.size();
    }

    inline bool run()
    {
        return std::all_of(m_testcases.begin(), m_testcases.end(),
                           [](auto& tc) { return tc.run(); });
    }

private:
    std::vector<tests::Testcase> m_testcases;
};

}  // namespace research
