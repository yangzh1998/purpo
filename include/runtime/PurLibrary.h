//
// Created by YANG Zehai on 2021/3/24.
//

#ifndef PUR_RT_PUR_LIBRARY_H
#define PUR_RT_PUR_LIBRARY_H

#include "runtime/PurObject.h"

namespace pur {

namespace rt {

// When using asm to declare a function or a variable,
// in both Clang++ and G++, there wouldn't be a default name mangling.
// Clang++ and G++ would use the literal label of asm as the name in .o file
//
// However, at LLVM IR level, on some platform such as MachO,
// the name has a '\01' prefix (and would get rid of '\01' at .o level then).
// On platform such as Linux, no prefix is added to the name at IR level.
// What's the standard?
// In the metadata of an LLVM IR file, there's info of data layout.
// if (dataLayout.getGlobalPrefix() != '\0'), a '\01' prefix is set.
//
// Why not use extern "C"? It only supports POD struct return.

bool PurGetBool(const PurObject&) asm("PurGetBool");

PurObject PurAdd(const PurObject&, const PurObject&) asm("PurAdd");
PurObject PurMinus(const PurObject&, const PurObject&) asm("PurMinus");
PurObject PurMul(const PurObject&, const PurObject&) asm("PurMul");
PurObject PurDiv(const PurObject&, const PurObject&) asm("PurDiv");
PurObject PurMod(const PurObject&, const PurObject&) asm("PurMod");

PurObject PurEqual(const PurObject&, const PurObject&) asm("PurEqual");
PurObject PurNotEq(const PurObject&, const PurObject&) asm("PurNotEq");
PurObject PurLess(const PurObject&, const PurObject&) asm("PurLess");
PurObject PurLessEq(const PurObject&, const PurObject&) asm("PurLessEq");
PurObject PurGreater(const PurObject&, const PurObject&) asm("PurGreater");
PurObject PurGreaterEq(const PurObject&, const PurObject&) asm("PurGreaterEq");

PurObject PurNot(const PurObject&) asm("PurNot");
PurObject PurNeg(const PurObject&) asm("PurNeg");

PurObject PurSelfAdd(const PurObject&) asm("PurSelfAdd");
PurObject PurSelfMinus(const PurObject&) asm("PurSelfMinus");
PurObject PurSelfMul(const PurObject&) asm("PurSelfMul");
PurObject PurSelfDiv(const PurObject&) asm("PurSelfDiv");
PurObject PurSelfMod(const PurObject&) asm("PurSelfMod");

PurObject PurToI61(const PurObject&) asm("PurToI61");
PurObject PurToF61(const PurObject&) asm("PurToF61");
PurObject PurToStr(const PurObject&) asm("PurToStr");
PurObject PurEval(const PurObject&) asm("PurEval");

} // namespace pur::rt

} // namespace pur

#endif // PUR_RT_PUR_LIBRARY_H
