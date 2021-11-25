//
// Created by YANG Zehai on 2021/11/23.
//

#ifndef PUR_ERR_ERROR_H
#define PUR_ERR_ERROR_H

#include <string>
#include "parser/Location.h"

#ifndef ABSTRACT
#define ABSTRACT
#endif // ABSTRACT

namespace pur {

namespace err {

ABSTRACT class Error {
public:
  Error(const std::string* file = nullptr, const pars::Location* loc = nullptr);
  bool operator<(const Error&) const;
  virtual std::string GetMsg() const = 0;

private:
  const std::string* mFileName; // no ownership
  const pars::Location* mLocation; // no ownership

}; // ERROR

} // namespace pur::err

} // namespace pur

#endif // PUR_ERR_ERROR_H
