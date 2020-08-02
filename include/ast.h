#pragma once
#include <string>
#include <memory>
#include <utility>
#include <vector>

//===----------------------------------------------------------------------===//
// Abstract Syntax Tree (aka Parse Tree)
//===----------------------------------------------------------------------===//
namespace llvm {
    class Value;
}
/// ExprAST - Base class for all expression nodes.
    class ExprAST {
    public:
        virtual ~ExprAST() = default;
        virtual llvm::Value* codegen() = 0;
    };

/// NumberExprAST - Expression class for numeric literals like "1.0".
    class NumberExprAST : public ExprAST {
        double Val;

    public:
        explicit NumberExprAST(double Val) : Val(Val) {}

        llvm::Value *codegen() override;
    };

/// VariableExprAST - Expression class for referencing a variable, like "a".
    class VariableExprAST : public ExprAST {
        std::string Name;

    public:
        explicit VariableExprAST(std::string Name) : Name(std::move(Name)) {}
        llvm::Value *codegen() override;
    };

/// BinaryExprAST - Expression class for a binary operator.
    class BinaryExprAST : public ExprAST {
        char Op;
        std::unique_ptr<ExprAST> LHS, RHS;
        llvm::Value *codegen() override;
    public:
        BinaryExprAST(char Op, std::unique_ptr<ExprAST> LHS,
                      std::unique_ptr<ExprAST> RHS)
                : Op(Op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}
    };

/// CallExprAST - Expression class for function calls.
    class CallExprAST : public ExprAST {
        std::string Callee;
        std::vector<std::unique_ptr<ExprAST>> Args;

    public:
        CallExprAST(std::string Callee,
                    std::vector<std::unique_ptr<ExprAST>> Args)
                : Callee(std::move(Callee)), Args(std::move(Args)) {}
        llvm::Value *codegen() override;
    };

/// PrototypeAST - This class represents the "prototype" for a function,
/// which captures its name, and its argument names (thus implicitly the number
/// of arguments the function takes).
    class PrototypeAST {
        std::string Name;
        std::vector<std::string> Args;

    public:
        PrototypeAST(std::string Name, std::vector<std::string> Args)
                : Name(std::move(Name)), Args(std::move(Args)) {}

        const std::string &getName() const { return Name; }
        virtual llvm::Value *codegen();
    };

/// FunctionAST - This class represents a function definition itself.
    class FunctionAST {
        std::unique_ptr<PrototypeAST> Proto;
        std::unique_ptr<ExprAST> Body;

    public:
        FunctionAST(std::unique_ptr<PrototypeAST> Proto,
                    std::unique_ptr<ExprAST> Body)
                : Proto(std::move(Proto)), Body(std::move(Body)) {}
        llvm::Value *codegen();
    };

