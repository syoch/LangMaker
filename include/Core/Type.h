#pragma once

namespace LangMaker::Core {

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

}