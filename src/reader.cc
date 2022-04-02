#include <iostream>
#include <stdexcept>
#include "common.h"
#include "BNF_Reader/Item.h"
#include "BNF_Reader/Reader.h"
#include "Utils.h"
struct FailedToRead : std::exception {
  char const* what() const noexcept override {
    return "failed to read";
  }
};

namespace LangMaker::BNF_Reader {

bool Reader::check() {
  return cur != source.end();
}

bool Reader::eat(char const* str) {
  if( !check() ) {
    return false;
  }

  if( *cur == str ) {
    ate = cur++;
    return true;
  }

  return false;
}

void Reader::expect(char const* str) {
  if( !eat(str) ) {
    std::cout << "expected '" << str << "'" << std::endl;
    exit(1);
  }
}

BNFItem Reader::factor() {
  if( cur == source.end() ) {
    std::cout << "syntax err" << std::endl;
    exit(1);
  }

  if( eat("(") ) {
    auto&& item = this->top();
    expect(")");
    return item;
  }

  auto st = getStrT(*cur);
  BNFItem item;

  switch( st ) {
    case StringType::Alphabets: {
      item.kind = BNF_VAR;
      item.name = *cur;
      cur++;
      break;
    }

    case StringType::String: {
      item.kind = BNF_STR;
      item.name = cur->substr(1, cur->length() - 2);
      cur++;
      break;
    }

    default:
      throw FailedToRead();
  }

  return item;
}

BNFItem Reader::repeat() {
  auto&& x = factor();

  if( eat("*") ) {
    x.item.reset(x.clone());
    x.kind = BNF_REPEAT;
  }
  else if( eat("?") ) {
    x.item.reset(x.clone());
    x.kind = BNF_OPTION;
  }

  return x;
}

BNFItem Reader::list() {
  BNFItem item{ .kind = BNF_LIST };

  try {
    while( check() ) {
      item.list.emplace_back(repeat());
    }
  }
  catch( ... ) { }

  return item.list.size() == 1 ? item.list[0] : item;
  return item;
}

BNFItem Reader::separator() {
  BNFItem item { .kind = BNF_SEPARATE };

  while( check() ) {
    item.list.emplace_back(list());

    if( !eat("|") ) {
      break;
    }
  }

  return item.list.size() == 1 ? item.list[0] : item;
}

BNFItem Reader::define() {
  if( getStrT(*cur) != StringType::Alphabets ) {
    return this->separator();
  }

  if( (cur + 1) < source.end() && cur[1] == "=" ) {
    BNFItem item = { .kind = ItemKind::BNF_DEFINE };

    item.name = *cur;

    cur += 2;
    item.item.reset(new BNFItem(this->separator()));

    return item;
  }

  return this->separator();
}

BNFItem Reader::top() {
  return this->define();
}

} // namespace LangMaker::BNF_Reader