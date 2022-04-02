#pragma once

namespace LangMaker::Core {

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

}