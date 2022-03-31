#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <tuple>

#define  alert  fprintf(stderr,"\t#Alert %s:%d\n",__FILE__,__LINE__)

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

namespace LangMaker {

// forward declarations
namespace Core {
  struct Object;
}

enum TokenKind {
  TOK_NAME,
  TOK_STR,
  TOK_PUNCTUATER,
  TOK_END
};

struct Token {
  TokenKind kind;
  Token* back;
  Token* next;
  std::string str;
  size_t pos;

  Token(TokenKind kind = TOK_NAME)
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

// BNF Reader
namespace BNF_Reader {

namespace BNFContext {



} // namespace BNFContext

class Reader {
  Token* cur;
  Token* ate;
  
  std::vector<

public:
  explicit Reader(Token* token) :cur(token), ate(nullptr) { }

  
};

} // namespace BNF_Reader

namespace Core {

enum TypeKind {
  TYPE_INT,
  TYPE_NONE
};

struct Type {
  TypeKind kind;
  
  Type(TypeKind kind = TYPE_NONE)
    : kind(kind)
  {
  }

  Type& operator = (TypeKind kind) {
    this->kind = kind;
    return *this;
  }
};

struct Object {
  Type type;
  size_t ref_count;

protected:
  Object() :ref_count(0) { }
};

struct ObjInt : Object {
  i64 val;

  ObjInt(i64 val = 0)
    : val(val)
  {
    this->type = TYPE_INT;
  }
};

} // namespace Core

} // namespace LangMaker

