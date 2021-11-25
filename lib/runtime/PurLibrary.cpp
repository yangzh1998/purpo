//
// Created by YANG Zehai on 2021/3/24.
//

#include <cassert>
#include "runtime/PurLibrary.h"

using namespace pur;
using namespace pur::rt;

bool pur::rt::PurGetBool(const PurObject& obj) {
  if (obj.mType != PurValueType::kBool) {
    // TODO: error handling
  }
  return obj.GetBool();
}

static bool Equal(const PurObject& left, const PurObject& right) {
  // TODO: What about type cast?
  if (*(uint64_t*)(&left) == *(uint64_t*)(&right)) {
    return true;
  }
  if (left.mType == PurValueType::kStr && right.mType == PurValueType::kStr) {
    return *(std::string*)(left.GetPtr()) == *(std::string*)(right.GetPtr());
  }
  return false;
}

PurObject pur::rt::PurEqual(const PurObject& left, const PurObject& right) {
  PurObject obj;
  obj.mType = PurValueType::kBool;
  obj.SetBool(Equal(left, right));
  return obj;
}

PurObject pur::rt::PurAdd(const PurObject& left, const PurObject& right) {
  // TODO: What about type cast?
  PurObject obj;
  obj.mType = left.mType; // TODO: F61 + I61
  switch (left.mType) {
    case PurValueType::kI61:
      obj.SetI61(left.GetI61() + right.GetI61());
      break;
    case PurValueType::kF61:
      obj.SetF61(left.GetF61() + right.GetF61());
      break;
    case PurValueType::kStr:
      obj.SetPtr(new std::string(*(std::string*)(left.GetPtr())));
      ((std::string*)obj.GetPtr())->append(*(std::string*)(right.GetPtr()));
      break;
    case PurValueType::kArray:
      // TODO: placement new
      break;
    default:
      assert(false); // TODO: Error Handling
  }
  return obj;
}
