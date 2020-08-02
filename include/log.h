#pragma once

#include <iostream>
#include <memory>
#include "ast.h"
/// LogError* - These are little helper functions for error handling.
inline std::unique_ptr<ExprAST> LogError(const char *Str) {
    std::cerr <<"Error: "<< Str<<'\n';
    return nullptr;
}