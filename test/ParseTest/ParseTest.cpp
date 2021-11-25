//
// Created by YANG Zehai on 2021/3/13.
//

#include <cassert>
#include <cstdio>
#include <fstream>
#include <memory>
#include "parser/Scanner.h"
#include "parser/Parser.h"
#include "AST/Printer.h"

using namespace pur;
using namespace pur::pars;

class RAII {
public:
  std::ofstream outputWriter;
  std::ifstream outputReader, keyReader;

  ~RAII() {
    if (outputWriter.is_open()) {
      outputWriter.close();
    }
    if (outputReader.is_open()) {
      outputReader.close();
    }
    if (keyReader.is_open()) {
      keyReader.close();
    }
  }
}; // RAII

Parser gParser(new Scanner());
RAII gRAII;

int main(int argc, char** argv) {
  if (argc != 4) {
    std::puts("ERROR: Expect 3 arguments.");
    return 0;
  }
  std::string inputFile(argv[1]);
  gParser.Init(inputFile);
  std::unique_ptr<ast::ASTRoot> tree = gParser.Parse();
  gRAII.outputWriter.open(argv[2]);
  ast::Printer printer = ast::Printer(gRAII.outputWriter);
  tree->Accept(printer);
  gRAII.outputWriter.close();

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

