//
// Created by YANG Zehai on 2021/3/1.
//

#ifndef PUR_PARS_SCANNER_H
#define PUR_PARS_SCANNER_H

#include <string>
#include <fstream>
#include <memory>
#include <sstream>
#include "parser/Token.h"
#include "parser/Location.h"

namespace pur {

namespace pars {

/**
 * Each file has its own Scanner.
 */
class Scanner {
public:
  Scanner();
  ~Scanner();
  Scanner(const Scanner&) = delete;
  Scanner& operator=(const Scanner&) = delete;

  // Not trying to open the file in the constructor in case error handling.
  void Init(const std::string& filePath);
  std::unique_ptr<Token> GetNextToken();

private:
  std::ifstream mInputFileStream;
  std::stringbuf mStringBuffer;
  std::string mFileName;
  Location mCurrentLocation;

  enum {
    kInitial,
    kWord,
    kNum,
    kNumWithPoint,
    kQuotation,
    kEscape,
    kNextExpectAnd,
    kNextExpectOr,
    kNextMayBeEq,
    kNextMayBeColon,
    kComment
  } mState;

}; // Scanner

} // namespace pur::pars

} // namespace pur

#endif // PUR_PARS_SCANNER_H
