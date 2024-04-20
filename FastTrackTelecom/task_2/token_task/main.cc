#include <iostream>
#include <vector>
#include <memory>
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

struct SqrToken {
};

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
  while (std::isdigit(symbol) && pos < input.size()) {
    value = value * 10 + ToDigit(symbol);
    symbol = static_cast<unsigned char>(input[++pos]);
  }
  return Number{value};
}

Token ParseName(const std::string& input, size_t& pos) {
  auto symbol = static_cast<unsigned char>(input[pos]);
  std::string nameTok;

  while ((std::isalpha(symbol) && pos < input.size())) {
    nameTok += symbol;
    symbol = static_cast<unsigned char>(input[++pos]);
  }
  if (nameTok.size() == 0) {
    nameTok += symbol;
    ++pos;
  }
  if (auto it = kName2Token.find(nameTok); it != kName2Token.end()) {
      return it->second;
  } else {
    return UnknownToken{nameTok};
  }
}

std::vector<Token> Tokenize(const std::string& input) {
  std::vector<Token> tokens;
  const size_t size = input.size();
  size_t pos = 0;
  while (pos < size) {
    const auto symbol = static_cast<unsigned char>(input[pos]);
    if (std::isspace(symbol)) {
      ++pos;
    } else if (std::isdigit(symbol)) {
      tokens.emplace_back(ParseNumber(input, pos));
    } else if (auto it = kSymbol2Token.find(symbol); it != kSymbol2Token.end()) {
      tokens.emplace_back(it->second);
      ++pos;
    } else {
      tokens.emplace_back(ParseName(input, pos));      
    }
  }
  return tokens;
}

int main() {
  std::string inputStr;
  std::getline(std::cin, inputStr);
  std::cout << "your line: " << inputStr << std::endl;
  auto tokenLine = Tokenize(inputStr);
  for (auto it = tokenLine.begin(); it != tokenLine.end(); it++)
  if (std::holds_alternative<UnknownToken>(*it)) {
    std::cout << std::get<UnknownToken>(*it).value << std::endl;
  }
  std::cout << "tokenLine size: " << tokenLine.size() << std::endl;
  return 0;
}