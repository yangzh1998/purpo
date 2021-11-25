//
// Created by YANG Zehai on 2021/11/15.
//

#include <iostream>

#include "util/IndentPrintWriter.h"

using namespace pur;
using namespace pur::ut;


IndentPrintWriter::IndentPrintWriter(std::ostream& os):
    mLevel(0), mOut(os), mHead(true) {
  /* empty */
}

void IndentPrintWriter::IncIndent() {
  mLevel ++;
}

void IndentPrintWriter::DecIndent() {
  if (mLevel > 0) mLevel --;
}

IndentPrintWriter& IndentPrintWriter::PrintLn(const std::string& str) {
  if (mHead) {
    for (int i = 0; i < mLevel; i ++) {
      mOut << "    ";
    }
  }
  mOut << str << std::endl;
  mHead = true;
  return *this;
}

IndentPrintWriter& IndentPrintWriter::PrintLn() {
  if (mHead) {
    for (int i = 0; i < mLevel; i ++) {
      mOut << "    ";
    }
  }
  mOut << std::endl;
  mHead = true;
  return *this;
}

IndentPrintWriter& IndentPrintWriter::Print(const std::string& str) {
  if (mHead) {
    for (int i = 0; i < mLevel; i ++) {
      mOut << "    ";
    }
  }
  mOut << str;
  mHead = false;
  return *this;
}


