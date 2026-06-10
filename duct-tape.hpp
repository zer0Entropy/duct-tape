#ifndef DUCT_TAPE_HPP
#define DUCT_TAPE_HPP

#include "include/core/engine.hpp"

static std::unique_ptr<DuctTape::Engine> instance;

DuctTape::Engine& GetInstance();

void Init();

#endif // DUCT_TAPE_HPP