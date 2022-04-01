#include "lang.h"

namespace LangMaker::BNF_Reader {
  std::string BNFItem::to_string(BNFItem const& item) {
    switch( item.kind ) {
      case BNF_DEFINE:
        return item.name + " = " + to_string(*item.item);

      case BNF_SEPARATE:
        return join(" | ", item.list, to_string);

      case BNF_LIST:
        return join(" ", item.list, to_string);

      case BNF_STR:
      case BNF_VAR:
        return item.name;

    }

    return "";
  }

  std::string BNFItem::to_data_string(BNFItem const& item) {
    switch( item.kind ) {
      case BNF_DEFINE:
        return item.name + " = " + to_data_string(*item.item);

      case BNF_SEPARATE:
        return join(" | ", item.list, to_data_string);

      case BNF_LIST: {

      }
        return "BNF_LIST(" + join(" ", item.list, to_data_string) + ")";

      case BNF_STR:
      case BNF_VAR:
        return item.name;

    }

    return "";
  }
}