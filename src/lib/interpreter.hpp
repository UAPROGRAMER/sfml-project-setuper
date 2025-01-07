#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "include.hpp"
#include "lexer.hpp"

class Interpreter {
private:
  std::vector<Token> &tokens;
  Token current;
  uint64_t size;
  uint64_t index;

  std::unordered_map<std::string, std::string> variables;

public:
  Interpreter(std::vector<Token> &tokens)
      : tokens(tokens), current(Token(TokenType::NOOP)), size(tokens.size()),
        index(-1) {
    advance();
    variables["name"] = "Project1";
    variables["version"] = "2.5.1";
    variables["libs"] = "window system graphics audio networking";
    variables["cxxs"] = "11";
    variables["cxxsr"] = "True";
    variables["link"] =
        "sfml-window sfml-system sfml-graphics sfml-audio sfml-networking";
  }

  void advance() {
    current = (++index < size) ? tokens.at(index) : Token(TokenType::NOOP);
  }

  void check(TokenType type) {
    if (current.type != type) {
      std::cerr << "[ ERROR ]: Unexpected token.\n";
      exit(1);
    }
  }

  std::unordered_map<std::string, std::string> run() {
    while (current.type != TokenType::NOOP) {
      if (current.type == TokenType::EOL)
        advance();
      else
        storeVar();
    }

    return variables;
  }

  void storeVar() {
    check(TokenType::LITERAL);
    std::string varName = current.value;
    advance();
    check(TokenType::EQUAL);
    advance();
    check(TokenType::LITERAL);
    std::string varValue = current.value;
    advance();

    while (current.type == TokenType::LITERAL) {
      varValue += ' ' + current.value;
      advance();
    }

    variables[varName] = varValue;
  }
};

#endif
