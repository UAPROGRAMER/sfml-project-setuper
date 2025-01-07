#ifndef LEXER_HPP
#define LEXER_HPP

#include "include.hpp"

enum class TokenType : uint8_t {
  LITERAL,
  EQUAL,
  EOL,
  NOOP,
};

class Token {
public:
  TokenType type;
  std::string value;

  Token(TokenType type) : type(type), value("") {}

  Token(TokenType type, std::string value) : type(type), value(value) {}

  void print() const {
    std::cout << '(' << static_cast<int>(type) << ',' << value << ')';
  }
};

class Lexer {
private:
  std::string &sourcecode;
  char current;
  size_t size;
  size_t index;

public:
  Lexer(std::string &sourcecode)
      : sourcecode(sourcecode), size(this->sourcecode.size()), index(-1) {
    advance();
  }

  void advance() { current = (++index < size) ? sourcecode.at(index) : '\0'; }

  std::vector<Token> tokenize() {
    std::vector<Token> tokens;

    Token newToken = next_token();
    while (newToken.type != TokenType::NOOP) {
      tokens.push_back(newToken);
      newToken = next_token();
    }
    tokens.push_back(newToken);

    return tokens;
  }

  Token next_token() {
    while (current == ' ' || current == '\t')
      advance();

    if (isalnum(current) || current == '_' || current == '.' || current == '-')
      return tokenize_LITERAL();

    Token result(TokenType::NOOP);
    switch (current) {
    case '\0':
      result = Token(TokenType::NOOP);
      break;
    case '\n':
      result = Token(TokenType::EOL);
      break;
    case '=':
      result = Token(TokenType::EQUAL);
      break;
    default:
      std::cerr << "[ ERROR ]: Bad char.\n";
      exit(1);
    }

    advance();

    return result;
  }

  Token tokenize_LITERAL() {
    std::stringstream buf;
    while (isalnum(current) || current == '_' || current == '.' ||
           current == '-') {
      buf << current;
      advance();
    }
    return Token(TokenType::LITERAL, buf.str());
  }
};

#endif
