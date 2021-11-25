//
// Created by YANG Zehai on 2021/3/1.
//

#include <ios>
#include <cstdlib>
#include <cstdio>
#include "parser/Scanner.h"

using namespace pur;
using namespace pur::pars;

Scanner::Scanner() {
  /* empty */
}

Scanner::~Scanner() {
  if (mInputFileStream.is_open()) {
    mInputFileStream.close();
  }
}

void Scanner::Init(const std::string& filePath) {
  mInputFileStream.open(filePath, std::ios::in);
  if (mInputFileStream.fail()) {
    std::printf("ERROR: Fail to open the file \"%s\"\n", filePath.c_str());
    std::exit(0);
  }
  mFileName = filePath;
  mCurrentLocation = {1, 1};
  mState = kInitial;
}

static Token* NewKeyword(int tc, const Location& loc) {
  Token* token = new Token();
  token->mCode = tc;
  token->mSemanticValue.reset(new SemanticValue());
  token->mSemanticValue->mLocation = loc;
  return token;
}

std::unique_ptr<Token> Scanner::GetNextToken() {
  Token* token = nullptr;
  int escapeCount = 0; // HACK: Used to calculate the length of a string const
  while (!token) {
    switch (mState) {
      case kInitial: {
        switch (mInputFileStream.peek()) {
          case '.':
          case ',':
          case ';':
          case '(':
          case ')':
          case '[':
          case ']':
          case '{':
          case '}':
            token = NewKeyword(mInputFileStream.get(), mCurrentLocation);
            mCurrentLocation.mColumn ++;
            break;
          case '<':
          case '>':
          case '=':
          case '!':
          case '+':
          case '-':
          case '*':
          case '/':
          case '%':
            mStringBuffer.sputc(mInputFileStream.get());
            // No change to mCurrentLocation
            mState = kNextMayBeEq;
            break;
          case ':':
            mInputFileStream.get();
            // No change to mCurrentLocation
            mState = kNextMayBeColon;
            break;
          case '&':
            mInputFileStream.get();
            mCurrentLocation.mColumn ++;
            mState = kNextExpectAnd;
            break;
          case '|':
            mInputFileStream.get();
            mCurrentLocation.mColumn ++;
            mState = kNextExpectOr;
            break;
          case '\"':
            mInputFileStream.get();
            mCurrentLocation.mColumn ++;
            mState = kQuotation;
            break;
          case ' ':
            mInputFileStream.get();
            mCurrentLocation.mColumn ++;
            break;
          case '\n':
            mInputFileStream.get();
            mCurrentLocation.mLine ++;
            mCurrentLocation.mColumn = 1;
            break;
          case EOF:
            token = new Token();
            token->mCode = EOF;
            break;
          case '#':
            mInputFileStream.get();
            mCurrentLocation.mColumn ++;
            mState = kComment;
            break;
          case '_':
            mState = kWord;
            mStringBuffer.sputc(mInputFileStream.get());
            break;
          default:
            char c = mInputFileStream.peek();
            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
              mStringBuffer.sputc(mInputFileStream.get());
              mState = kWord;
            } else if (c >= '0' && c <= '9') {
              mStringBuffer.sputc(mInputFileStream.get());
              mState = kNum;
            } else {
              std::printf("ERROR: %s: %d:%d, Unrecognized character \'%c\'\n",
                          mFileName.c_str(), mCurrentLocation.mLine,
                          mCurrentLocation.mColumn, c);
              std::exit(0);
            }
            break;
        }
        break;
      }
      case kWord: {
        switch (mInputFileStream.peek()) {
          case '_':
            mStringBuffer.sputc(mInputFileStream.get());
            break;
          default:
            char c = mInputFileStream.peek();
            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
                (c >= '0' && c <= '9')) {
              mStringBuffer.sputc(mInputFileStream.get());
            } else {
              std::string word = mStringBuffer.str();
              auto mapIter = Token::gStringToToken.find(word);
              if (mapIter == Token::gStringToToken.end()) {
                token = NewKeyword(kIdentifier, mCurrentLocation);
                token->mSemanticValue->mIdentifier = word;
              } else {
                token = NewKeyword(mapIter->second, mCurrentLocation);
              }
              mStringBuffer.str("");
              mCurrentLocation.mColumn += word.size();
              mState = kInitial;
            }
            break;
        }
        break;
      }
      case kNum: {
        switch (mInputFileStream.peek()) {
          case '.':
            mStringBuffer.sputc(mInputFileStream.get());
            mState = kNumWithPoint;
            break;
          default:
            char c = mInputFileStream.peek();
            if (c >= '0' && c <= '9') {
              mStringBuffer.sputc(mInputFileStream.get());
            } else {
              std::string numStr = mStringBuffer.str();
              mStringBuffer.str("");
              token = NewKeyword(kI61Const, mCurrentLocation);
              token->mSemanticValue->mI61Const = std::stoll(numStr);
              mCurrentLocation.mColumn += numStr.size();
              mState = kInitial;
            }
            break;
        }
        break;
      }
      case kNumWithPoint: {
        char c = mInputFileStream.peek();
        if (c >= '0' && c <= '9') {
          mStringBuffer.sputc(mInputFileStream.get());
        } else {
          std::string numStr = mStringBuffer.str();
          mStringBuffer.str("");
          token = NewKeyword(kF61Const, mCurrentLocation);
          token->mSemanticValue->mF61Const = std::stod(numStr);
          mCurrentLocation.mColumn += numStr.size();
          mState = kInitial;
        }
        break;
      }
      case kQuotation: {
        switch (mInputFileStream.peek()) {
          case '\"':
            mInputFileStream.get();
            token = NewKeyword(kStrConst, mCurrentLocation);
            token->mSemanticValue->mStrConst = mStringBuffer.str();
            mStringBuffer.str("");
            mCurrentLocation.mColumn += token->mSemanticValue->mStrConst.size()
                + 2 + escapeCount;
            escapeCount = 0;
            mState = kInitial;
            break;
          case '\\':
            mInputFileStream.get();
            mState = kEscape;
            break;
          case '\n':
            std::printf("ERROR: %s, %d:%d, Unexpected newline in the string\n",
                        mFileName.c_str(), mCurrentLocation.mLine,
                        mCurrentLocation.mColumn);
            std::exit(0);
          case '\t':
            std::printf("ERROR: %s: %d:%d, Unexpected tab in the string\n",
                        mFileName.c_str(), mCurrentLocation.mLine,
                        mCurrentLocation.mColumn);
            std::exit(0);
          case EOF:
            std::printf("ERROR: %s: %d:%d, Unterminated string\n",
                        mFileName.c_str(), mCurrentLocation.mLine,
                        mCurrentLocation.mColumn);
            std::exit(0);
          default:
            mStringBuffer.sputc(mInputFileStream.get());
            break;
        }
        break;
      }
      case kEscape: {
        escapeCount ++;
        switch (mInputFileStream.peek()) {
          case 't':
            mStringBuffer.sputc('\t');
            mState = kQuotation;
            break;
          case 'n':
            mStringBuffer.sputc('\n');
            mState = kQuotation;
            break;
          case '\\':
            mStringBuffer.sputc('\\');
            mState = kQuotation;
            break;
          case '\n':
            std::printf("ERROR: %s: %d:%d, Unexpected newline in the string\n",
                        mFileName.c_str(), mCurrentLocation.mLine,
                        mCurrentLocation.mColumn);
            std::exit(0);
          case '\t':
            std::printf("ERROR: %s: %d:%d, Unexpected tab in the string\n",
                        mFileName.c_str(), mCurrentLocation.mLine,
                        mCurrentLocation.mColumn);
            std::exit(0);
          case EOF:
            std::printf("ERROR: %s: %d:%d, Unterminated string\n",
                        mFileName.c_str(), mCurrentLocation.mLine,
                        mCurrentLocation.mColumn);
            std::exit(0);
          default:
            std::printf("ERROR: %s: %d:%d, Bad \'\\\'\n", mFileName.c_str(),
                        mCurrentLocation.mLine, mCurrentLocation.mColumn);
            std::exit(0);
        }
        break;
      }
      case kNextExpectAnd: {
        switch (mInputFileStream.peek()) {
          case '&':
            mInputFileStream.get();
            mCurrentLocation.mColumn ++;
            token = NewKeyword(kAnd, mCurrentLocation);
            mState = kInitial;
            break;
          default:
            std::printf("ERROR: %s: %d:%d, Expect another \'&\'\n",
                        mFileName.c_str(), mCurrentLocation.mLine,
                        mCurrentLocation.mColumn);
            std::exit(0);
        }
        break;
      }
      case kNextExpectOr: {
        switch (mInputFileStream.peek()) {
          case '|':
            mInputFileStream.get();
            mCurrentLocation.mColumn ++;
            token = NewKeyword(kOr, mCurrentLocation);
            mState = kInitial;
            break;
          default:
            std::printf("ERROR: %s: %d:%d, Expect another \'|\'\n",
                        mFileName.c_str(), mCurrentLocation.mLine,
                        mCurrentLocation.mColumn);
            std::exit(0);
        }
        break;
      }
      case kNextMayBeEq: {
        switch (mInputFileStream.peek()) {
          case '=':
            switch (mStringBuffer.sbumpc()) {
              case '+':
                token = NewKeyword(kAddAssign, mCurrentLocation);
                break;
              case '-':
                token = NewKeyword(kSubAssign, mCurrentLocation);
                break;
              case '*':
                token = NewKeyword(kMulAssign, mCurrentLocation);
                break;
              case '/':
                token = NewKeyword(kDivAssign, mCurrentLocation);
                break;
              case '%':
                token = NewKeyword(kModAssign, mCurrentLocation);
                break;
              case '<':
                token = NewKeyword(kLE, mCurrentLocation);
                break;
              case '>':
                token = NewKeyword(kGE, mCurrentLocation);
                break;
              case '=':
                token = NewKeyword(kEq, mCurrentLocation);
                break;
              case '!':
                token = NewKeyword(kNotEq, mCurrentLocation);
                break;
            }
            mInputFileStream.get();
            mCurrentLocation.mColumn += 2;
            mState = kInitial;
            break;
          default:
            token = NewKeyword(mStringBuffer.sbumpc(), mCurrentLocation);
            mCurrentLocation.mColumn ++;
            mState = kInitial;
            break;
        }
        mStringBuffer.str("");
        break;
      }
      case kNextMayBeColon: {
        switch (mInputFileStream.peek()) {
          case ':':
            token = NewKeyword(kField, mCurrentLocation);
            mInputFileStream.get();
            mCurrentLocation.mColumn += 2;
            mState = kInitial;
            break;
          default:
            token = NewKeyword(':', mCurrentLocation);
            mCurrentLocation.mColumn ++;
            mState = kInitial;
            break;
        }
        break;
      }
      case kComment: {
        switch (mInputFileStream.get()) {
          case '\n':
            mCurrentLocation.mLine ++;
            mCurrentLocation.mColumn = 1;
            mState = kInitial;
            break;
          default:
            break;
        }
        break;
      }
    }
  }
  return std::unique_ptr<Token>(token);
}
