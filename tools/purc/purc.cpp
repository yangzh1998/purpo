//
// Created by YANG Zehai on 2021/3/1.
//

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <memory>
#include "option/Option.h"
#include "parser/Parser.h"
#include "parser/Scanner.h"
#include "AST/ASTRoot.h"

using namespace pur;

std::vector<std::string> gInputFiles;
std::string gOutputFile;
opt::Option gOption;

pars::Parser gParser(new pars::Scanner());

void PrintHelp();

void ParseOption(int argc, char** argv) {
  std::vector<std::string> args;
  for (int i = 1; i < argc; i ++) {
    args.emplace_back(argv[i]);
  }
  for (int i = 0; i < args.size(); i ++) {
    auto pair = opt::Option::sMap.find(args[i]);
    if (pair == opt::Option::sMap.end()) {
      gInputFiles.push_back(args[i]);
    } else {
      switch (pair->second) {
        case opt::OptionKey::kHelp:
          PrintHelp();
          exit(0);
        case opt::OptionKey::kOutput:
          gOutputFile = args[++i];
          break;
        case opt::OptionKey::kWerror:
          gOption.mWerror = true;
          break;
        case opt::OptionKey::kWSuppress:
          gOption.mWSuppress = true;
          break;
      }
    }

    // check
    if (gInputFiles.size() == 0) {
      std::puts("purc: Error: no input file");
      exit(1);
    }
    if (gInputFiles.size() > 1 && gOutputFile != "") {
      std::puts("purc: Error: specified output file with multiple input files");
      exit(1);
    }
    if (gOutputFile != "") {
      // TODO: check dir
    }

  }
}

int main(int argc, char** argv) {
  ParseOption(argc, argv);
  for (const std::string& inputFile : gInputFiles) {
    gParser.Init(inputFile);
    std::unique_ptr<ast::ASTRoot> tree = gParser.Parse();
  }
  return 0;
}

void PrintHelp() {
  std::puts("OVERVIEW: purpo compiler(purc)");
  std::puts("");
  std::puts("USAGE: purc [options] file");
  std::puts("");
  std::puts("DRIVER OPTIONS:");
  std::puts("  -h, --help");
  std::puts("    Display available options.");
  std::puts("");
  std::puts("  -o <file>");
  std::puts("    Write output to file.");
  std::puts("");
  std::puts("  -Werror");
  std::puts("    Treat all warnings as errors.");
  std::puts("");
  std::puts("  -w");
  std::puts("    Suppress all warnings.");
  std::puts("");
}