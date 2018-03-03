//
// Created by ahoma on 3/3/18.
//

#include "Parser.h"
#include <iostream>

int main() {
  std::string expression;
  std::getline(std::cin, expression);

  Parser test_parser(expression.c_str());
  std::cout << test_parser.Evaluate() << std::endl;
  return 0;
}