//
// Created by YANG Zehai on 2021/11/23.
//

#ifndef PUR_ERR_WARNING_H
#define PUR_ERR_WARNING_H

#include "error/Error.h"

#ifndef ABSTRACT
#define ABSTRACT
#endif // ABSTRACT

namespace pur {

namespace err {

ABSTRACT class Warning : public Error {

}; // Warning

} // namespace pur::err

} // namespace pur
