#pragma once

#include <memory>

namespace LangMaker::BNF_Reader {

enum ItemKind {
  BNF_DEFINE,
  BNF_OPTION,
  BNF_REPEAT,
  BNF_SEPARATE,
  BNF_LIST,
  BNF_STR,
  BNF_VAR
};

struct BNFItem {
  ItemKind kind;

  std::string name;
  std::shared_ptr<BNFItem> item;

  std::vector<BNFItem> list;

  static std::string to_string(BNFItem const& item);
  static std::string to_data_string(BNFItem const& item);

  BNFItem* clone() {
    return new BNFItem(*this);
  }
};

}