//
// Created by dgmuller on 6/15/26.
//

#include <iostream>
#include "../include/result.hpp"

void DisplayTestResult(const TestResult& result) {
    std::cout << "Result: ";
    if(result.passed) {
        std::cout << "Passed!" << std::endl;
    } // if test passed
    else {
        std::cout << "Failed!" << std::endl;
        std::cout << "Details: " << result.details << std::endl;
    } // else test failed
}