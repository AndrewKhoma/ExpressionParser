//
// Created by ahoma on 3/3/18.
//

#ifndef MATHEXPRESSION_PARSER_H
#define MATHEXPRESSION_PARSER_H

#include <utility>
#include <string>
#include <vector>

struct Expression {
  explicit Expression(std::string _token) : token(std::move(_token)) {};
  Expression(std::string _token, Expression argument) : token(std::move(_token)), args{std::move(argument)} {};
  Expression(std::string _token, Expression lhs, Expression rhs) : token(std::move(_token)), args{std::move(lhs),
                                                                                                  std::move(rhs)} {};

  std::string token;
  std::vector<Expression> args;
};

class Parser {
 public:
  Parser() = delete;

  explicit Parser(const char *input) : input_expression_(input) {};

  double Evaluate();
 private:
  Expression Parse();
  std::string ParseToken();
  Expression ParseSimpleExpression();
  Expression ParseComplicatedExpression(int priority);

  int GetPriority(const std::string &binary_operator);

  double EvaluateExpression(const Expression &expression);

  const char *input_expression_;
};

#endif //MATHEXPRESSION_PARSER_H
