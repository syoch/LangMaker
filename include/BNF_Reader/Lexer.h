#pragma once

namespace LangMaker::BNF_Reader {

class Lexer {
  std::string const& source;
  size_t position;

  bool check();
  char peek();
  void pass_space();

public:
  explicit Lexer(std::string const& source)
    : source(source), position(0) { }
  
  void lex(std::vector<std::string>& out);


};

}