#include "calculator.h"
#include "eval.h"
#include <vector>

int64_t EvaluateExpression(const std::string& expression) {
    std::stringstream ss(expression);
    Tokenizer tok(&ss);
    auto expr = ParseExpression(&tok);

    return expr->Evaluate();
}