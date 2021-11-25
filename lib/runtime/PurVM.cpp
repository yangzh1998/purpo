//
// Created by YANG Zehai on 2021/3/25.
//

#include "runtime/PurVM.h"
#include "runtime/PurHeapDataWrapper.h"

using namespace pur;
using namespace pur::rt;

size_t gStackSize;
size_t pur::rt::gStackPointer;
PurObject* pur::rt::gStack;

size_t gGenerationNum;

void pur::rt::VMInit(size_t stackSize, size_t generationNum) {
  gStackSize = stackSize;
  gStackPointer = gStackSize;
  gStack = reinterpret_cast<PurObject*>(new char[gStackSize]);

  gGenerationNum = generationNum;
}

static char* Alloc(size_t size) {
  // TODO: set PurHeapDataWrapper's mSize, mValid, mMarked
  return 0; // TODO
}

char* pur::rt::AllocArray() {
  char* start = Alloc(sizeof(PurHeapDataWrapper<PurArrayData>));
  char* data = (char*)&(((PurHeapDataWrapper<PurArrayData>*)start)->mData);
  new (data) PurArrayData();
  return data;
}

char* pur::rt::AllocMap() {
  char* start = Alloc(sizeof(PurHeapDataWrapper<PurMapData>));
  char* data = (char*)&(((PurHeapDataWrapper<PurMapData>*)start)->mData);
  new (data) PurMapData();
  return data;
}