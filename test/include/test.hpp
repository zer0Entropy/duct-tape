//
// Created by dgmuller on 6/13/26.
//

#ifndef DT_TEST_HPP
#define DT_TEST_HPP

#define DT_TEST

#include <string>
#include "result.hpp"

using TestName = std::string;

struct Test {
    enum class TestID {
        WindowInitTest,
        WindowCloseTest
    };
    Test() = default;
    virtual ~Test() = 0;
    virtual TestID GetID() const = 0;
    virtual TestName GetName() const = 0;
    virtual TestResult Run() = 0;
};

void DisplayTestIntro(const Test& test);

#endif //DT_TEST_HPP