//
// Created by YANG Zehai on 2021/3/25.
//

#ifndef PUR_RT_PUR_VM_H
#define PUR_RT_PUR_VM_H

#include <cstddef>
#include "PurObject.h"

namespace pur {

namespace rt {

extern size_t gStackPointer asm("purSP");
extern PurObject* gStack asm("purStack");

void VMInit(size_t stackSize=1024*1024,
            size_t generationNum=10) asm("PurVMInit");

char* AllocArray() asm("PurAllocArray");
char* AllocMap() asm("PurAllocMap");

} // namespace pur::rt

} // namespace pur

#endif // PUR_RT_PUR_VM_H
