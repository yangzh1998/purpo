//
// Created by YANG Zehai on 2021/11/25.
//

#ifndef PUR_OPT_OPTION_H
#define PUR_OPT_OPTION_H

#include <unordered_map>
#include <string>

namespace pur {

namespace opt {

enum class OptionKey {
  kHelp,
  kOutput,
  kWerror,
  kWSuppress,
};

struct Option {
  static std::unordered_map<std::string, OptionKey> sMap;
  bool mWerror = false; // treat warnings as errors
  bool mWSuppress = false;
}; // option

} // namespace pur::opt

} // namespace pur

#endif // PUR_OPT_OPTION_H
