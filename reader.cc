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
  if( *cur == str ) {
    ate = cur++;
    return true;
  }

  return false;
}

BNFItem Reader::factor() {

}

BNFItem Reader::list() {
  BNFItem item;

  try {
    while( check() ) {
      item.list.emplace_back(factor());
    }
  }
  catch( ... ) { }

  return item;
}

BNFItem Reader::separator() {
  BNFItem item { .kind = ItemKind::BNF_SEPARATE };

  while( check() ) {
    item.list.emplace_back(list());

    if( !eat("|") ) {
      break;
    }
  }

  return item;
}

BNFItem Reader::top() {
  return this->define();
}

} // namespace LangMaker::BNF_Reader