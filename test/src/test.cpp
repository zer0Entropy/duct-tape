//
// Created by dgmuller on 6/13/26.
//

#include <iostream>
#include "../include/test.hpp"

Test::~Test() {}

void DisplayTestIntro(const Test& test) {
    std::cout << "Running test #" << std::to_string(static_cast<int>(test.GetID()));
    std::cout << ": (" << test.GetName() << ")" << std::endl;
}