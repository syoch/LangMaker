#include "common.h"
#include "BNF_Reader/Item.h"
#include "Utils.h"

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

      case BNF_REPEAT:
        return "REPEAT(" + to_data_string(*item.item) + ")";

      case BNF_OPTION:
        return "OPTION(" + to_data_string(*item.item) + ")";

      case BNF_SEPARATE:
        return "SEPARATE(" + join(" | ", item.list, to_data_string) + ")";

      case BNF_LIST: {
        return "LIST(" + join(", ", item.list, to_data_string) + ")";
      }

      case BNF_STR:
        return '"' + item.name + '"';

      case BNF_VAR:
        return item.name;
    }

    return "";
  }
}