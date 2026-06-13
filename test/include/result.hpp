//
// Created by dgmuller on 6/13/26.
//

#ifndef DT_TEST_RESULT_HPP
#define DT_TEST_RESULT_HPP

#include <string>

struct TestResult {
    std::string details;
    bool passed;

    explicit TestResult():
        passed(false) {

    }

    ~TestResult() {

    }
};

#endif //DT_TEST_RESULT_HPP
