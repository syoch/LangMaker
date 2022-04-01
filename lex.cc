#include "lang.h"

static char const* reservedTokens[] = {
  "=",
  "(",
  ")",
  "*",
  "?",
  "|",
};

namespace LangMaker::BNF_Reader {

bool Lexer::check() {
  return this->position < this->source.length();
}

char Lexer::peek() {
  return this->source[this->position];
}

void Lexer::pass_space() {
  while( check() && peek() <= ' ' ) this->position++;
}

void Lexer::lex(std::vector<std::string>& out) {
  pass_space();

  for( ; check(); ) {
    auto ch = peek();
    std::string s;

    if( isdigit(ch) ) {
      while( check() && isdigit(ch = peek()) ) {
        s += ch;
        this->position++;
      }
    }
    else if( isalpha(ch) ) {
      while( check() && (isalnum(ch = peek()) || ch == '_') ) {
        s += ch;
        this->position++;
      }
    }
    else if( ch == '"' ) {
      this->position++;

      while( check() && peek() != '"' ) {
        s += peek();
        this->position++;
      }

      this->position++;
      s='"'+s+'"';
    }
    else {
      for( std::string&& x : reservedTokens ) {
        if( this->position+x.length()<=source.length()
        &&source.substr(this->position,x.length())==x) {
          this->position += x.length();
          s=std::move(x);
          goto done;
        }
      }

      std::cerr << "position=" << this->position << ": unknown token." << std::endl;
      exit(1);
    }

  done:;
    out.emplace_back(s);
    pass_space();
  }
}

} // namespace LangMaker::BNF_Reader