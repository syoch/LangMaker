#include "lang.h"

namespace LangMaker::BNF_Reader {

bool Lexer::check() {
  return this->position < this->source.length();
}

char Lexer::peek() {
  return this->source[this->position];
}

void Lexer::lex(std::vector<std::string>& out) {
  for( ; check(); this->position++ ) {
    auto ch = peek();

    if( isdigit(ch) ) {
      
    }
  }
}

} // namespace LangMaker::BNF_Reader