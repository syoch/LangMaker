#pragma once

#include "BNF_Reader/Item.h"

namespace LangMaker::BNF_Reader {

class Reader {
  using Iterator = typename std::vector<std::string>::iterator;
  using ConstIterator = typename std::vector<std::string>::const_iterator;

  //Token* cur;
  //Token* ate;

  ConstIterator cur, ate;
  std::vector<std::string> const& source;
  
  std::vector<BNFItem*> ctxlist;

  bool check();
  bool eat(char const*);
  void expect(char const*);

  enum class StringType {
    Number,
    Alphabets,
    String,
    Other,
    None
  };

  static StringType getStrT(std::string const& s) {
    if( s.empty() ) {
      return StringType::None;
    }

    if( isdigit(s[0]) ) {
      return StringType::Number;
    }
    else if( isalpha(s[0]) ) {
      return StringType::Alphabets;
    }
    else if( s[0] == '"' ) {
      return StringType::String;
    }

    return StringType::Other;
  }

public:
  explicit Reader(std::vector<std::string> const& source)
    : source(source)
  {
    this->cur = this->source.begin();
  }

  BNFItem factor();
  BNFItem repeat();
  BNFItem list();
  BNFItem separator();
  BNFItem define();
  BNFItem top();
};

}