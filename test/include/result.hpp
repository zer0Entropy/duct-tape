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

    explicit TestResult(std::string_view details, bool passed):
        details(std::string{details}), passed(passed) {

    }

    ~TestResult() {

    }
};

void DisplayTestResult(const TestResult& result);

#endif //DT_TEST_RESULT_HPP
