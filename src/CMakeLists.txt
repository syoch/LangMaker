add_executable(
  langmaker

  BNFItem.cc
  lex.cc
  main.cc
  reader.cc
  run_node.cc
)

target_include_directories(langmaker PRIVATE "../include")