#include <iostream>
#include <vector>
#include <memory>
#include <array>
#include <variant>
#include <unordered_map>
#include <string>

// (1 + 2) * 3 / 4 + 5 * (6 - 7)

// 1. Токенизация
// 2. Парсер (построение дерева разбора выражения)

// +, -, *, /, %

struct OpeningBracket {};

struct ClosingBracket {};

struct Number {
  int value;
};

struct UnknownToken {
  std::string value;
};

struct MinToken {};

struct AbsToken {};

struct Plus {};

struct Minus {};

struct Multiply {};

struct Modulo {};

struct Divide {};

struct SqrToken {};

struct MaxToken {};


using Token = std::variant<OpeningBracket, ClosingBracket, Number, UnknownToken, MinToken, AbsToken, Plus, Minus, Multiply, Modulo, Divide, SqrToken, MaxToken>;

const std::unordered_map<char, Token> kSymbol2Token{
    {'(', OpeningBracket{}}, {')', ClosingBracket{}}, {'+', Plus{}}, {'-', Minus{}}, {'*', Multiply{}}, {'/', Divide{}}, {'%', Modulo{}}};

const std::unordered_map<std::string, Token> kName2Token{
    {"sqr", SqrToken{}}, {"max", MaxToken{}}, {"min", MinToken{}}, {"abs", AbsToken{}}};


int ToDigit(unsigned char symbol) {
  return symbol - '0';
}

Number ParseNumber(const std::string& input, size_t& pos) {
  int value = 0;
  auto symbol = static_cast<unsigned char>(input[pos]);
  while (std::isdigit(symbol)) {
    value = value * 10 + ToDigit(symbol);
    if (pos == input.size() - 1) {
      break;
    }
    symbol = static_cast<unsigned char>(input[++pos]);
  }
  return Number{value};
}

Token ParseName(const std::string& input, size_t& pos) {
  auto symbol = static_cast<unsigned char>(input[pos]);
  std::string nameTok;
  int read = 0;

  while ((std::isalpha(symbol) && pos < input.size()) && read < 3) {
    nameTok[read] = symbol;
    symbol = static_cast<unsigned char>(input[++pos]);
    ++read;
  }
  std::cout << "is eq ? " << nameTok.compare("sqr") << std::endl;
  if (auto it = kName2Token.find(nameTok); it != kName2Token.end()) {
      std::cout << "Success!" << std::endl;
      return it->second;
  } else {
    return UnknownToken{};
  }
}

std::vector<Token> Tokenize(const std::string& input) {
  std::vector<Token> tokens;
  const size_t size = input.size();
  size_t pos = 0;
  while (pos < size - 1) {
    const auto symbol = static_cast<unsigned char>(input[pos]);
    if (std::isspace(symbol)) {
      ++pos;
    } else if (std::isdigit(symbol)) {
      tokens.emplace_back(ParseNumber(input, pos));
    } else if (auto it = kSymbol2Token.find(symbol); it != kSymbol2Token.end()) {
      tokens.emplace_back(it->second);
      ++pos;
    } else {
      std::cout << "ParseName1" << std::endl;
      tokens.emplace_back(ParseName(input, pos));      
    }
  }
  return tokens;
}

// void checkTokens(const std::vector<Token> tokens) {

// }

int main() {
  std::string inputStr;
  std::getline(std::cin, inputStr);
  std::cout << "your line: " << inputStr << std::endl;
  auto tokenLine = Tokenize(inputStr);
  std::cout << inputStr.size() << std::endl;
  return 0;
}