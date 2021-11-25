//
// Created by YANG Zehai on 2021/11/25.
//

#include "option/Option.h"

using namespace pur;
using namespace pur::opt;

std::unordered_map<std::string, OptionKey> Option::sMap = {
    {"-h", OptionKey::kHelp},
    {"--help", OptionKey::kHelp},
    {"-o", OptionKey::kOutput},
    {"-Werror", OptionKey::kWerror},
    {"-w", OptionKey::kWSuppress}
};
