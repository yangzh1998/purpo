//
// Created by YANG Zehai on 2021/11/23.
//

#include "error/Error.h"

using namespace pur;
using namespace pur::err;

Error::Error(const std::string* file, const pars::Location* loc):
mFileName(file), mLocation(loc) {
  /* empty */
}

bool Error::operator<(const Error& right) const {
  int cmp = mFileName->compare(*(right.mFileName));
  if (cmp) return cmp < 0;
  if (mLocation->mLine != right.mLocation->mLine) {
    return mLocation->mLine < right.mLocation->mLine;
  }
  return mLocation->mColumn < right.mLocation->mColumn;
}
