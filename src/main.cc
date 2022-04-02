#include <iostream>
#include <fstream>
#include "common.h"
#include "BNF_Reader/Lexer.h"
#include "BNF_Reader/Reader.h"

int main(int argc, char** argv) {
  using namespace LangMaker;

  std::ifstream ifs{ "test.txt" };
  std::string src;

  for( std::string l; std::getline(ifs, l); ) {
    src += l + "\n";
  }

  std::vector<std::string> s;

  BNF_Reader::Lexer lexer(src);
  lexer.lex(s);

  // for(auto&&i:s) std::cout<<i<<std::endl;

  BNF_Reader::Reader reader(s);

  BNF_Reader::BNFItem item = reader.top();

  std::cout << BNF_Reader::BNFItem::to_data_string(item) << std::endl;

}