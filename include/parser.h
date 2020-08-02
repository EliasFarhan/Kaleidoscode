#pragma once
#include <memory>

class FunctionAST;
class ExprAST;
class PrototypeAST;
std::unique_ptr<ExprAST> ParseExpression();
std::unique_ptr<FunctionAST> ParseDefinition();
std::unique_ptr<ExprAST> ParseParenExpr();
std::unique_ptr<PrototypeAST> ParseExtern();
std::unique_ptr<FunctionAST> ParseTopLevelExpr();
int GetCurTok();
int getNextToken();
