//
// Created by efarhan on 02.08.20.
//
#include "ast.h"
#include "token.h"
#include "log.h"
#include "parser.h"
//===----------------------------------------------------------------------===//
// Top-Level parsing
//===----------------------------------------------------------------------===//

static void HandleDefinition() {
    if (ParseDefinition()) {
        std::cout<<"Parsed a function definition.\n";
    } else {
        // Skip token for error recovery.
        getNextToken();
    }
}

static void HandleExtern() {
    if (ParseExtern()) {
        std::cout<<"Parsed an extern\n";
    } else {
        // Skip token for error recovery.
        getNextToken();
    }
}

static void HandleTopLevelExpression() {
    // Evaluate a top-level expression into an anonymous function.
    if (ParseTopLevelExpr()) {
        std::cout<<"Parsed a top-level expr\n";
    } else {
        // Skip token for error recovery.
        getNextToken();
    }
}

/// top ::= definition | external | expression | ';'
static void MainLoop() {
    while (true) {
        std::cout<<"ready> ";
        switch (GetCurTok()) {
            case tok_eof:
                return;
            case ';': // ignore top-level semicolons.
                getNextToken();
                break;
            case tok_func:
                HandleDefinition();
                break;
            case tok_extern:
                HandleExtern();
                break;
            default:
                HandleTopLevelExpression();
                break;
        }
    }
}

//===----------------------------------------------------------------------===//
// Main driver code.
//===----------------------------------------------------------------------===//

int main() {


    // Prime the first token.
    std::cout<< "ready> ";
    getNextToken();

    // Run the main "interpreter loop" now.
    MainLoop();

    return 0;
}