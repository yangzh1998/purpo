//
// Created by YANG Zehai on 2021/3/1.
//

#ifndef PUR_PARS_TOKEN_H
#define PUR_PARS_TOKEN_H

#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include "parser/SemanticValue.h"

namespace pur {

namespace pars {

enum TokenCode {
  kFunc = 256,
  kReturn = 257,
  kFor = 258,
  kIn = 259,
  kIf = 260,
  kElse = 261,
  kWhile = 262,
  kBreak = 263,
  kContinue = 264,
  kTrue = 265,
  kFalse = 266,
  kNull = 267,
  kImport = 268,
  kAs = 269,

  kAnd = 288,
  kOr = 289,
  kEq = 290,
  kNotEq = 291,
  kGE = 292,
  kLE = 293,
  kAddAssign = 294,
  kSubAssign = 295,
  kMulAssign = 296,
  kDivAssign = 297,
  kModAssign = 298,
  kField = 299,

  kIdentifier = 320,
  kI61Const = 321,
  kF61Const = 322,
  kStrConst = 323
}; // TokenCode

struct Token {
  int32_t mCode;
  std::unique_ptr<SemanticValue> mSemanticValue;

  static std::unordered_map<int, std::string> gTokenToString;
  static std::unordered_map<std::string, int> gStringToToken;
}; // Token

} // namespace pur::pars

} // namespace pur

#endif // PUR_PARS_TOKEN_H
