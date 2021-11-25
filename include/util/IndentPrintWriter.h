//
// Created by YANG Zehai on 2021/11/15.
//

#ifndef PUR_UTIL_INDENT_PRINT_WRITER_H
#define PUR_UTIL_INDENT_PRINT_WRITER_H

#include <iostream>

namespace pur {

namespace ut {

class IndentPrintWriter {
private:
  int mLevel;
  std::ostream& mOut;
  bool mHead;

public:
  explicit IndentPrintWriter(std::ostream& os = std::cout);
  void IncIndent();
  void DecIndent();
  IndentPrintWriter& Print(const std::string&);
  IndentPrintWriter& PrintLn(const std::string&);
  IndentPrintWriter& PrintLn();
}; // IndentPrintWriter

} // namespace pur::ut

} // namespace pur

#endif // PUR_UTIL_INDENT_PRINT_WRITER_H
