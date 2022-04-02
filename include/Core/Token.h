#pragma once

namespace LangMaker::Core {

enum TokenKind {
  TOK_INT,
  TOK_IDENT,
  TOK_RESERVED,
  TOK_END
};

struct Token {
  TokenKind kind;
  Token* back;
  Token* next;
  std::string str;
  size_t pos;

  Token(TokenKind kind = TOK_INT)
    : kind(kind),
      back(nullptr),
      next(nullptr),
      pos(0)
  {
  }

  Token(TokenKind kind, Token* back, size_t pos)
    : Token(kind)
  {
    this->back = back;
    this->pos = pos;

    if( back ) {
      back->next = this;
    }
  }
};

}