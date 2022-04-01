#include <stdexcept>
#include "lang.h"

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
  debug(
    alert;
    *cur;
  )

  if( cur == source.end() ) {
    std::cout << "syntax err" << std::endl;
    exit(1);
  }

  if( *cur == "(" ) {
    cur++;
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

    default:
      throw FailedToRead();
  }

  return item;
}

BNFItem Reader::list() {
  BNFItem item{ .kind = BNF_LIST };

  try {
    while( check() ) {
      item.list.emplace_back(factor());
    }
    
    alert;
  }
  catch( ... ) { }


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

  return item;
}

BNFItem Reader::define() {
  debug(
    alert;
    *cur;
  )

  //BNFItem item { .kind = ItemKind::BNF_DEFINE };

  if( getStrT(*cur) != StringType::Alphabets ) {
    alert;
    return this->separator();
  }

  if( cur[1] == "=" ) {
    BNFItem item = { .kind = ItemKind::BNF_DEFINE };

    item.name = *cur;
    
    cur += 2;
    item.item.reset(new BNFItem(this->separator()));

    return item;
  }

  return this->separator();
}

BNFItem Reader::top() {
  alert;
  *cur;

  return this->define();
}

} // namespace LangMaker::BNF_Reader