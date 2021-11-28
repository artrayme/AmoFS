//
// Created by artrayme on 11/28/21.
//

#ifndef AMOFS_TESTUS_COLOR_UTILS_H_
#define AMOFS_TESTUS_COLOR_UTILS_H_

#endif//AMOFS_TESTUS_COLOR_UTILS_H_

#include <ostream>
namespace Color {
enum Code {
  FG_RED = 31,
  FG_GREEN = 32,
  FG_BLUE = 34,
  FG_DEFAULT = 39,
  BG_RED = 41,
  BG_GREEN = 42,
  BG_BLUE = 44,
  BG_DEFAULT = 49
};
class Modifier {
  Code code;

 public:
  Modifier(Code pCode) : code(pCode) {}
  friend std::ostream &
  operator<<(std::ostream &os, const Modifier &mod) {
    return os << "\033[" << mod.code << "m";
  }
};
}// namespace Color