//
// Created by YANG Zehai on 2021/3/24.
//

#ifndef PUR_RT_PUR_OBJECT_H
#define PUR_RT_PUR_OBJECT_H

#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>

namespace pur {

namespace rt {

enum class PurValueType : uint8_t {
  kNull = 0,
  kBool = 1,
  kI61 = 2,
  kF61 = 3,
  kStr = 4,
  kArray = 5,
  kMap = 6
}; // PurValueType

struct PurObjHash;
struct PurObjEqual;
class PurObject;

typedef std::vector<PurObject> PurArrayData;
typedef std::unordered_map<PurObject, PurObject, PurObjHash, PurObjEqual>
    PurMapData;

class PurObject {
public:
  PurValueType mType : 3; // lowest 3 bits

private:
  uint64_t mContent : 61; // ownership: std::string

public:
  PurObject();
  ~PurObject();
  PurObject(const PurObject&);
  PurObject(PurObject&&);
  PurObject& operator=(const PurObject&);
  PurObject& operator=(PurObject&&);

  inline bool GetBool() const;
  inline void SetBool(bool);
  inline int64_t GetI61() const;
  inline void SetI61(int64_t);
  inline double GetF61() const;
  inline void SetF61(double);
  inline void* GetPtr() const;
  inline void SetPtr(void*);
}; // PurObject

inline bool PurObject::GetBool() const {
  return (bool)mContent;
}

inline void PurObject::SetBool(bool value) {
  mContent = (uint64_t)value;
}

inline int64_t PurObject::GetI61() const {
  return (int64_t)mContent;
}

inline void PurObject::SetI61(int64_t value) {
  mContent = (uint64_t)value;
}

inline double PurObject::GetF61() const {
  uint64_t temp = mContent << 3;
  double ret = *(double*)(&temp);
  return ret;
}

inline void PurObject::SetF61(double value) {
  mContent = (*(uint64_t*)&value) >> 3;
}

inline void* PurObject::GetPtr() const {
  return (void*)(mContent << 3);
}

inline void PurObject::SetPtr(void* ptr) {
  mContent = ((uint64_t)ptr) >> 3;
}


struct PurObjHash {
  int64_t operator()(const PurObject&) const;
}; // PurObjHash

struct PurObjEqual {
  bool operator()(const PurObject&, const PurObject&) const;
}; // PurObjEqual

} // namespace pur::rt

} // namespace pur

#endif // PUR_RT_PUR_OBJECT_H
