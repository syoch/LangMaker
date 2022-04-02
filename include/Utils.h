#pragma once

#include <concepts>
#include <ostream>
#include <vector>
#include <string>
#include <sstream>

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
