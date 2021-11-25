//
// Created by YANG Zehai on 2021/3/19.
//

#include <cstdio>
#include "parser/Token.h"

using namespace pur;
using namespace pur::pars;

std::unordered_map<int, std::string> Token::gTokenToString = {
    {kFunc, "func"},
    {kReturn, "return"},
    {kFor, "for"},
    {kIn, "in"},
    {kIf, "if"},
    {kElse, "else"},
    {kWhile, "while"},
    {kBreak, "break"},
    {kContinue, "continue"},
    {kTrue, "true"},
    {kFalse, "false"},
    {kNull, "null"},
    {kImport, "import"},
    {kAs, "as"},

    {kAnd, "&&"},
    {kOr, "||"},
    {kEq, "=="},
    {kNotEq, "!="},
    {kGE, ">="},
    {kLE, "<="},
    {kAddAssign, "+="},
    {kSubAssign, "-="},
    {kMulAssign, "*="},
    {kDivAssign, "/="},
    {kModAssign, "%="},
    {kField, "::"},

    {kIdentifier, "<identifier>"},
    {kI61Const, "<i61 const>"},
    {kF61Const, "<f61 const>"},
    {kStrConst, "<str const>"},

    {EOF, "<EOF>"},
    {'+', "+"},
    {'-', "-"},
    {'*', "*"},
    {'/', "/"},
    {'%', "%"},
    {'=', "="},
    {'>', ">"},
    {'<', "<"},
    {'.', "."},
    {',', ","},
    {';', ";"},
    {':', ":"},
    {'(', "("},
    {')', ")"},
    {'[', "["},
    {']', "]"},
    {'{', "{"},
    {'}', "}"}
};

std::unordered_map<std::string, int> Token::gStringToToken = {
    {"func", kFunc}, 
    {"return", kReturn},
    {"for", kFor},
    {"in", kIn},
    {"if", kIf},
    {"else", kElse},
    {"while", kWhile},
    {"break", kBreak},
    {"continue", kContinue},
    {"true", kTrue},
    {"false", kFalse},
    {"null", kNull},
    {"import", kImport},
    {"as", kAs}
};
