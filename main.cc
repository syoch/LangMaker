#include "lang.h"

int main(int argc, char** argv) {
  using namespace LangMaker;

  std::vector<std::string> s { "a", "=", "b", "|", "c" };

  BNF_Reader::Reader reader(s);

  BNF_Reader::BNFItem item = reader.top();

  std::cout << item.to_string() << std::endl;

}