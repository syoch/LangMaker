#include "lang.h"

namespace LangMaker::BNF_Reader {
  std::string BNFItem::to_string() const {
    switch( this->kind ) {
      case BNF_DEFINE:
        return this->name + " = " + this->item->to_string();

      case BNF_SEPARATE:
        return join(" | ", this->list);

      case BNF_LIST:
        return join(" ", this->list);

      case BNF_STR:
      case BNF_VAR:
        return this->name;

    }

    return "";
  }
}