#pragma once

#include <concepts>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <tuple>

#define  alert  fprintf(stderr,"\t#Alert %s:%d\n",__FILE__,__LINE__)
#define  debug(...) __VA_ARGS__

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

template <class T>
concept haveMethodToString = requires (T const& x) {
  x.to_string();
};

template <haveMethodToString T>
std::ostream& operator << (std::ostream& ost, T const& x) {
  return ost << x.to_string();
}

template <haveMethodToString T>
std::string join(std::string const& s, std::vector<T> const& vec) {
  std::stringstream ss;

  for( size_t i = 0; i < vec.size(); i++ ) {
    ss << vec[i];

    if( i < vec.size() - 1 ) {
      ss << s;
    }
  }

  return ss.str();
}

template <class T, class F>
std::string join(std::string const& s, std::vector<T> const& vec, F f) {
  std::stringstream ss;

  for( size_t i = 0; i < vec.size(); i++ ) {
    ss << f(vec[i]);

    if( i < vec.size() - 1 ) {
      ss << s;
    }
  }

  return ss.str();
}

namespace LangMaker {

// forward declarations
namespace Core {
  struct Object;
}

// BNF Reader
namespace BNF_Reader {

enum ItemKind {
  BNF_DEFINE,
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

};

class Lexer {
  std::string const& source;
  size_t position;

  bool check();
  char peek();

public:
  explicit Lexer(std::string const& source)
    : source(source), position(0) { }
  
  void lex(std::vector<std::string>& out);


};

class Reader {
  using Iterator = typename std::vector<std::string>::iterator;
  using ConstIterator = typename std::vector<std::string>::const_iterator;

  //Token* cur;
  //Token* ate;

  ConstIterator cur, ate;
  std::vector<std::string> const& source;
  
  std::vector<BNFItem*> ctxlist;

  bool check();
  bool eat(char const*);
  void expect(char const*);

  enum class StringType {
    Number,
    Alphabets,
    None
  };

  static StringType getStrT(std::string const& s) {
    if( s.empty() ) {
      return StringType::None;
    }

    if( isdigit(s[0]) ) {
      return StringType::Number;
    }
    else if( isalpha(s[0]) ) {
      return StringType::Alphabets;
    }

    return StringType::None;
  }

public:
  explicit Reader(std::vector<std::string> const& source)
    : source(source)
  {
    this->cur = this->source.begin();

    alert;
  }

  BNFItem factor();
  BNFItem list();
  BNFItem separator();
  BNFItem define();
  BNFItem top();
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

