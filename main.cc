#include "lang.h"

int main(int argc, char** argv) {
  using namespace LangMaker;

  std::vector<std::string> s { "a", "=", "b", "|", "c", "e" };

  BNF_Reader::Reader reader(s);

  BNF_Reader::BNFItem item = reader.top();

  std::cout << BNF_Reader::BNFItem::to_data_string(item) << std::endl;

}