//
// Created by YANG Zehai on 2021/3/13.
//

#include <cassert>
#include <cstdio>
#include <fstream>
#include <memory>
#include "parser/Scanner.h"
#include "parser/Token.h"

using namespace pur;
using namespace pur::pars;

class RAII {
public:
  FILE* outputWriter;
  std::ifstream outputReader, keyReader;

  ~RAII() {
    if (outputWriter) fclose(outputWriter);
    if (outputReader.is_open()) {
      outputReader.close();
    }
    if (keyReader.is_open()) {
      keyReader.close();
    }
  }
}; // RAII

Scanner gScanner;
RAII gRAII;

int main(int argc, char** argv) {
  if (argc != 4) {
    std::puts("ERROR: Expect 3 arguments.");
    return 0;
  }
  std::string inputFile(argv[1]);
  gScanner.Init(inputFile);
  gRAII.outputWriter = std::fopen(argv[2], "w");

  std::unique_ptr<Token> token;
  while (!(token.get()) || token->mCode!=EOF) {
    token = gScanner.GetNextToken();
    int code = token->mCode;
    const Location& loc = token->mSemanticValue->mLocation;
    switch (code) {
      case kIdentifier:
        std::fprintf(gRAII.outputWriter, "identifier:%s <%d:%d>\n",
                     token->mSemanticValue->mIdentifier.c_str(),
                     loc.mLine, loc.mColumn);
        break;
      case kI61Const:
        std::fprintf(gRAII.outputWriter, "i61Const:%lld <%d:%d>\n",
                     token->mSemanticValue->mI61Const,
                     loc.mLine, loc.mColumn);
        break;
      case kF61Const:
        std::fprintf(gRAII.outputWriter, "f61Const:%lf <%d:%d>\n",
                     token->mSemanticValue->mF61Const,
                     loc.mLine, loc.mColumn);
        break;
      case kStrConst:
        std::fprintf(gRAII.outputWriter, "strConst:\"%s\" <%d:%d>\n",
                     token->mSemanticValue->mStrConst.c_str(),
                     loc.mLine, loc.mColumn);
        break;
      default:
        if (code >= 256) {
          std::fprintf(gRAII.outputWriter, "%s <%d:%d>\n",
                       Token::gTokenToString[code].c_str(),
                       loc.mLine, loc.mColumn);
        } else if (code >= 0) {
          std::fprintf(gRAII.outputWriter, "%c <%d:%d>\n", code,
                       loc.mLine, loc.mColumn);
        }
        break;
    }
  }
  fclose(gRAII.outputWriter);

  // assert: The purpo source file has no lexical error.

  gRAII.outputReader.open(argv[2]);
  gRAII.keyReader.open(argv[3]);
  assert(!gRAII.outputReader.fail() && !gRAII.keyReader.fail());

  while (!gRAII.outputReader.eof() && !gRAII.keyReader.eof()) {
    std::string outputString, keyString;
    std::getline(gRAII.outputReader, outputString);
    std::getline(gRAII.keyReader, keyString);
    if (outputString != keyString) {
      std::puts("Fail!");
      return 0;
    }
  }
  if (!gRAII.outputReader.eof() || !gRAII.keyReader.eof()) {
    std::puts("Fail!");
    return 0;
  }

  std::puts("Success!");
  return 0;
}

