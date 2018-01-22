#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <cctype>
#include "calculator.h"

Tokenizer::Tokenizer(std::istream* in) : in_(in) {
    type_ = UNKNOWN;
}

void Tokenizer::Consume() {
    type_ = Tokenizer::UNKNOWN;
}

Tokenizer::TokenType Tokenizer::GetType(){
    while(type_ == Tokenizer::UNKNOWN){
        ReadNext();
    }
    return type_;
}

int64_t Tokenizer::GetNumber() {
    while(type_ == Tokenizer::UNKNOWN){
        ReadNext();
    }
    return number_;
}

char Tokenizer::GetSymbol() {
    while(type_ == Tokenizer::UNKNOWN){
        ReadNext();
    }
    return symbol_;
}

void Tokenizer::ReadNext(){
    *in_ >> std::ws;
    if(std::isdigit(in_->peek())){
        type_ = Tokenizer::NUMBER;
        *in_ >> number_;
    } else if(in_->peek() == EOF){
        type_ = Tokenizer::END;
    } else {
        type_ = Tokenizer::SYMBOL;
        symbol_ = in_->get();
    }
}

Const::Const(int64_t value) : value_(value) {}

int64_t Const::Evaluate() {
    return value_;
}

Sum::Sum(std::unique_ptr<Expression> lhd, std::unique_ptr<Expression> rhd) 
    : lhd_(std::move(lhd)), rhd_(std::move(rhd)) {}

int64_t Sum::Evaluate() {
    return lhd_->Evaluate() + rhd_->Evaluate();
}


Sub::Sub(std::unique_ptr<Expression> lhd, std::unique_ptr<Expression> rhd) 
    : lhd_(std::move(lhd)), rhd_(std::move(rhd)) {}

int64_t Sub::Evaluate() {
    return lhd_->Evaluate() - rhd_->Evaluate();
}

Mul::Mul(std::unique_ptr<Expression> lhd, std::unique_ptr<Expression> rhd) 
    : lhd_(std::move(lhd)), rhd_(std::move(rhd)) {}

int64_t Mul::Evaluate() {
    return lhd_->Evaluate() * rhd_->Evaluate();
}

Div::Div(std::unique_ptr<Expression> lhd, std::unique_ptr<Expression> rhd) 
    : lhd_(std::move(lhd)), rhd_(std::move(rhd)) {}

int64_t Div::Evaluate() {
    return lhd_->Evaluate() / rhd_->Evaluate();
}

UnaryMinus::UnaryMinus(std::unique_ptr<Expression> child) 
    : child_(std::move(child)) {}

int64_t UnaryMinus::Evaluate() {
    return -child_->Evaluate();
}

std::unique_ptr<Expression> ParseNode(Tokenizer* tok) {
    if(tok->GetType() == Tokenizer::NUMBER){
        auto node = std::make_unique<Const>(tok->GetNumber());
        tok->Consume();
        return node;
    } else if(tok->GetType() == Tokenizer::SYMBOL && tok->GetSymbol() == '-'){
        tok->Consume();
        return std::make_unique<UnaryMinus>(ParseNode(tok));
    } else if(tok->GetType() == Tokenizer::SYMBOL && tok->GetSymbol() == '('){
        tok->Consume();
        auto node = ParseExpression(tok);
        tok->Consume();
        return node;
    }
    return nullptr;
}

std::unique_ptr<Expression> ParseFactor(Tokenizer* tok) {
    auto factor = ParseNode(tok);
    while(tok->GetType() == Tokenizer::SYMBOL && (tok->GetSymbol() == '*' || tok->GetSymbol() == '/') ) {
        switch (tok->GetSymbol()) {
            case '*': {
                tok->Consume();
                factor = std::make_unique<Mul>(std::move(factor), ParseNode(tok));
                break;
            }
            case '/': {
                tok->Consume();
                factor = std::make_unique<Div>(std::move(factor), ParseNode(tok));
                break;
            }
        }
    }

    return factor;
}
std::unique_ptr<Expression> ParseExpression(Tokenizer* tok) {
    auto term = ParseFactor(tok);
    while(tok->GetType() == Tokenizer::SYMBOL && (tok->GetSymbol() == '+' || tok->GetSymbol() == '-')) {
        switch (tok->GetSymbol()) {
            case '+': {
                tok->Consume();
                term = std::make_unique<Sum>(std::move(term), ParseFactor(tok));
                break;
            }
            case '-': {
                tok->Consume();
                term = std::make_unique<Sub>(std::move(term), ParseFactor(tok));
                break;
            }
        }
    }

    return term;
}