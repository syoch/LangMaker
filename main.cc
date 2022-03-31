#include "lang.h"

int main(int argc, char** argv) {
  using namespace LangMaker;

  BNF_Reader::Reader reader({ "a = \"+\" | \"-\"" });

  BNF_Reader::BNFItem item = reader.top();

  

}