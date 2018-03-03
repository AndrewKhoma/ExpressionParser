//
// Created by ahoma on 3/3/18.
//

#include "Parser.h"

#include <stdexcept>
#include <cstring>
#include <cmath>

Expression Parser::Parse() {
  return ParseComplicatedExpression(0);
}

std::string Parser::ParseToken() {

  while (isspace(*input_expression_))
    ++input_expression_;

  if (isdigit(*input_expression_)) {
    std::string number;
    while (isdigit(*input_expression_) || *input_expression_ == '.')
      number.push_back(*input_expression_++);
    return number;
  }

  static const std::string tokens[] = {"+", "-", "^", "*", "/", "mod", "abs", "sin", "cos", "(", ")"};
  for (auto &t : tokens) {
    if (strncmp(input_expression_, t.c_str(), t.size()) == 0) {
      input_expression_ += t.size();
      return t;
    }
  }

  return "";
}

Expression Parser::ParseSimpleExpression() {
  auto token = ParseToken();
  if (token.empty())
    throw std::runtime_error("Invalid input");

  if (token == "(") {
    auto result = Parse();
    if (ParseToken() != ")")
      throw std::runtime_error("Expected ')'");
    return result;
  }

  if (isdigit(token[0]))
    return Expression(token);

  return Expression(token, ParseSimpleExpression());
}

int Parser::GetPriority(const std::string &binary_operator) {
  if (binary_operator == "+")
    return 1;
  if (binary_operator == "-")
    return 1;
  if (binary_operator == "*")
    return 2;
  if (binary_operator == "/")
    return 2;
  if (binary_operator == "mod")
    return 2;
  if (binary_operator == "^")
    return 3;
  return 0;
}

Expression Parser::ParseComplicatedExpression(int priority) {
  auto left_expr = ParseSimpleExpression();

  for (;;) {
    auto operation = ParseToken();
    auto operation_priority = GetPriority(operation);
    if (operation_priority <= priority) {
      input_expression_ -= operation.size();
      return left_expr;
    }

    auto right_expr = ParseComplicatedExpression(priority);
    left_expr = Expression(operation, left_expr, right_expr);
  }
}

double Parser::EvaluateExpression(const Expression &expression) {

  switch (expression.args.size()) {
    case 2: {
      auto a = EvaluateExpression(expression.args[0]);
      auto b = EvaluateExpression(expression.args[1]);
      if (expression.token == "+")
        return a + b;
      if (expression.token == "-")
        return a - b;
      if (expression.token == "*")
        return a * b;
      if (expression.token == "/")
        return a / b;
      if (expression.token == "^")
        return std::pow(a, b);
      if (expression.token == "mod")
        return (int) a % (int) b;
      throw std::runtime_error("Unknown binary operator");
    }

    case 1: {
      auto a = EvaluateExpression(expression.args[0]);
      if (expression.token == "+")
        return +a;
      if (expression.token == "-")
        return -a;
      if (expression.token == "abs")
        return std::abs(a);
      if (expression.token == "sin")
        return sin(a);
      if (expression.token == "cos")
        return cos(a);
      throw std::runtime_error("Unknown unary operator");
    }

    case 0: return strtod(expression.token.c_str(), nullptr);
    default: throw std::runtime_error("Unknown expression type");
  }
}

double Parser::Evaluate() {
  Expression total_expression = this->Parse();
  return EvaluateExpression(total_expression);
}
