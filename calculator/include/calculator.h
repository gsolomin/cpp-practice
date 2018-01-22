#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <cctype>

class Tokenizer {
public:
    Tokenizer(std::istream* in);
    enum TokenType {
        UNKNOWN,
        NUMBER,
        SYMBOL,
        END
    };
    void Consume();
    TokenType GetType();
    int64_t GetNumber();
    char GetSymbol();

private:
    std::istream* in_;
    TokenType type_;
    int64_t number_;
    char symbol_;

    void ReadNext();
};

class Expression {
public:
    virtual ~Expression() {}
    virtual int64_t Evaluate() = 0;
};

class Const : public Expression {
public:
    explicit Const(int64_t value);
    int64_t Evaluate() override;
private:
    int64_t value_;
};

class Sum : public Expression{
public:
    Sum(std::unique_ptr<Expression> lhd, std::unique_ptr<Expression> rhd);
    int64_t Evaluate() override;
private:
    std::unique_ptr<Expression> lhd_;
    std::unique_ptr<Expression> rhd_;
};

class Sub : public Expression{
public:
    Sub(std::unique_ptr<Expression> lhd, std::unique_ptr<Expression> rhd);
    int64_t Evaluate() override;
private:
    std::unique_ptr<Expression> lhd_;
    std::unique_ptr<Expression> rhd_;
};

class Mul : public Expression{
public:
    Mul(std::unique_ptr<Expression> lhd, std::unique_ptr<Expression> rhd);
    int64_t Evaluate() override;
private:
    std::unique_ptr<Expression> lhd_;
    std::unique_ptr<Expression> rhd_;
};

class Div : public Expression{
public:
    Div(std::unique_ptr<Expression> lhd, std::unique_ptr<Expression> rhd);
    int64_t Evaluate() override;
private:
    std::unique_ptr<Expression> lhd_;
    std::unique_ptr<Expression> rhd_;
};

class UnaryMinus : public Expression{
public:
    UnaryMinus(std::unique_ptr<Expression> child);
    int64_t Evaluate() override;
private:
    std::unique_ptr<Expression> child_;
};

std::unique_ptr<Expression> ParseExpression(Tokenizer* tok);
std::unique_ptr<Expression> ParseNode(Tokenizer* tok);
std::unique_ptr<Expression> ParseFactor(Tokenizer* tok);
std::unique_ptr<Expression> ParseExpression(Tokenizer* tok);