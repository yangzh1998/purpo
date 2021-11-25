//
// Created by YANG Zehai on 2021/3/24.
//

#include "runtime/PurObject.h"
#include "runtime/PurLibrary.h"

using namespace pur;
using namespace pur::rt;

PurObject::PurObject(): mType(PurValueType::kNull), mContent(0) {
  /* empty */
}

PurObject::~PurObject() {
  if (mType == PurValueType::kStr) {
    delete (std::string*)GetPtr();
  }
}

PurObject::PurObject(const PurObject& obj) {
  mType = obj.mType;
  if (mType == PurValueType::kStr) {
    SetPtr(new std::string(*(std::string*)(obj.GetPtr())));
  } else {
    mContent = obj.mContent;
  }
}

PurObject::PurObject(PurObject&& obj) {
  mType = obj.mType;
  mContent = obj.mContent;
  if (mType == PurValueType::kStr) {
    obj.SetPtr(nullptr);
  }
}

PurObject& PurObject::operator=(const PurObject& obj) {
  mType = obj.mType;
  if (mType == PurValueType::kStr) {
    SetPtr(new std::string(*(std::string*)(obj.GetPtr())));
  } else {
    mContent = obj.mContent;
  }
  return *this;
}

PurObject& PurObject::operator=(PurObject&& obj) {
  mType = obj.mType;
  mContent = obj.mContent;
  if (mType == PurValueType::kStr) {
    obj.SetPtr(nullptr);
  }
  return *this;
}

int64_t PurObjHash::operator()(const PurObject& obj) const {
  switch (obj.mType) {
    case PurValueType::kBool:
      return std::hash<bool>()(obj.GetBool());
    case PurValueType::kI61:
      return std::hash<int64_t>()(obj.GetI61());
    case PurValueType::kF61:
      return std::hash<double>()(obj.GetF61());
    case PurValueType::kStr:
      return std::hash<std::string>()(*(std::string*)obj.GetPtr());
    default:
      // TODO: error handling
      break;
  }
  return 0;
}

bool PurObjEqual::operator()(const PurObject& l, const PurObject& r) const {
  if (*(uint64_t*)(&l) == *(uint64_t*)(&r)) {
    return true;
  }
  if (l.mType == PurValueType::kStr && r.mType == PurValueType::kStr) {
    return *(std::string*)(l.GetPtr()) == *(std::string*)(r.GetPtr());
  }
  return false;
}